#include "data_utils.h"
#include "gpio_utils.h"
#include "bme280_utils.h"

void update_values(double *humidity, double *temperature, int presence[], int openning[]){
    get_bme280_temperature_humidity(temperature, humidity);

    get_inpt_device_on_off(presence, openning);
}

void send_data(double *humidity, double *temperature, int presence[], int openning[]){
    // TODO send data to central server
    printf("H %.2lf\nT %.2lf\n", *humidity, *temperature);
    for(int i = 0; i < 2; i++){
        printf("P%d %d\n", i+1, presence[i]);
    }
    for(int i = 0; i < 6; i++){
        printf("O%d %d\n", i+1, openning[i]);
    }
}