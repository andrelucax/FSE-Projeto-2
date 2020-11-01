#include "data_utils.h"
#include "gpio_utils.h"
#include "bme280_utils.h"
#include "tcp_client.h"

void update_values(double *humidity, double *temperature, int presence[], int openning[], int air[], int lamp[]){
    get_bme280_temperature_humidity(temperature, humidity);

    get_inpt_device_on_off(presence, openning);

    get_outp_device_on_off(lamp, air);
}

int send_data(double *humidity, double *temperature, int presence[], int openning[], int air[], int lamp[]){
    if (send_message_to_server(humidity, temperature, presence, openning)){
        return 1;
    }
    return 0;
}
