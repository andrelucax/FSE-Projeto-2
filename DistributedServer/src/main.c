#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// My libs
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
