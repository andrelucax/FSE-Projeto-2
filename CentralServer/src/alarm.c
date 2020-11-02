#include "alarm.h"
#include "gpio_defines.h"

void check_alarm(int presence[], int openning[]){
    for(int i = 0; i < 2; i++){
        if(presence[i] == ON){
            // play_sound();
            return;
        }
    }
    for(int i = 0; i < 6; i++){
        if(openning[i] == ON){
            // play_sound();
            return;
        }
    }
}