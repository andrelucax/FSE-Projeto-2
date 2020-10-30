#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// My Headers
#include "gpio_utils.h"
#include "bme280_utils.h"

// Handle signals
void sig_handler(int signum);
void update_values();
void send_data();

int main(){
    printf("Starting BCM...\n");
    if(init_bcm()){
        printf("Failed to start BCM\n");
        exit(-1);
    }
    printf("BCM started\n");

    printf("Starting BME280...\n");
    if (setup_bme280()){
        printf("Failed to start BME280\n");
        exit(-2);
    }
    printf("BME280 started\n");
	
    printf("Handling signals...\n");
    signal(SIGALRM, sig_handler);
    ualarm(1000000, 1000000);
    printf("All good to go\n");
	
    sig_handler(SIGALRM);
    return 0;
}

void sig_handler(int signum){
    if (signum == SIGALRM){
        // Every 1 sec
        double humidity = 0, temperature = 0;
        int presence[2], openning[6];
        update_values(&humidity, &temperature, presence, openning);
        send_data(&humidity, &temperature, presence, openning);
    }
}

void update_values(double *humidity, double *temperature, int presence[], int openning[]){
    get_bme280_temperature_humidity(temperature, humidity);

    get_inpt_device_on_off(presence, openning);
}

void send_data(double *humidity, double *temperature, int presence[], int openning[]){
    // TODO send data to central server
    printf("H %.2lf\nT %.2lf\n", *humidity, *temperature);
    for(int i = 0; i < *(&presence + 1) - presence; i++){
        printf("P%d %d\n", i+1, presence[i]);
    }
    for(int i = 0; i < *(&openning + 1) - openning; i++){
        printf("O%d %d\n", i+1, openning[i]);
    }
}