#include <unistd.h>
#include <stdio.h>

#include "air_controller.h"
#include "gpio_utils.h"

void *control_temperature(void *_air_mrt){
    struct air_mrt * m_air_mrt = (struct air_mrt *) _air_mrt;
    while(1){
        int _air_mode = m_air_mrt->_air_mode;
        float _reference_temperature = m_air_mrt->_reference_temperature;
        float _temperature = m_air_mrt->_temperature;

        if(_air_mode == TEMPERATURE){
            if(_temperature < _reference_temperature - HISTERESIS/2){
                outp_device_on_off(AIR, 1, OFF);
                outp_device_on_off(AIR, 2, OFF);
            }
            else if(_temperature > _reference_temperature + HISTERESIS/2){
                outp_device_on_off(AIR, 1, ON);
                outp_device_on_off(AIR, 2, ON);
            }
        }

        usleep(500000);
    }
}