#include "gpio_utils.h"
#include <stdio.h>

int init_bcm(){
    if (!bcm2835_init()){
        return 1;
    }

    bcm2835_gpio_fsel(LAMP1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LAMP3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP4, BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_fsel(AIR1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AIR2, BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_fsel(PRESENCE1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PRESENCE2, BCM2835_GPIO_FSEL_INPT);

	bcm2835_gpio_fsel(OPENNING1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPENNING2, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(OPENNING3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPENNING4, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(OPENNING5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPENNING6, BCM2835_GPIO_FSEL_INPT);

    return 0;
}

int outp_device_on_off(int device_type, int device_id, int on_off){
    if(on_off != ON && on_off != OFF){
        return 1;
    }
    if(device_type == AIR){
        if(device_id == 1){
            bcm2835_gpio_write(AIR1, on_off);
        }
        else if(device_id == 2){
            bcm2835_gpio_write(AIR2, on_off);
        }
        else{
            return 2;
        }
    }
    else if(device_type == LAMP){
        if(device_id == 1){
            bcm2835_gpio_write(LAMP1, on_off);
        }
        else if(device_id == 2){
            bcm2835_gpio_write(LAMP2, on_off);
        }
        else if(device_id == 3){
            bcm2835_gpio_write(LAMP3, on_off);
        }
        else if(device_id == 4){
            bcm2835_gpio_write(LAMP4, on_off);
        }
        else{
            return 3;
        }
    }
    else{
        return 4;
    }

    return 0;
}

void get_inpt_device_on_off(int presence[], int openning[]){
    presence[0] = bcm2835_gpio_lev(PRESENCE1);
    presence[1] = bcm2835_gpio_lev(PRESENCE2);

    openning[0] = bcm2835_gpio_lev(OPENNING1);
    openning[1] = bcm2835_gpio_lev(OPENNING2);
    openning[2] = bcm2835_gpio_lev(OPENNING3);
    openning[3] = bcm2835_gpio_lev(OPENNING4);
    openning[4] = bcm2835_gpio_lev(OPENNING5);
    openning[5] = bcm2835_gpio_lev(OPENNING6);
}

void get_outp_device_on_off(int lamp[], int air[]){
    air[0] = bcm2835_gpio_lev(AIR1);
    air[1] = bcm2835_gpio_lev(AIR2);

    lamp[0] = bcm2835_gpio_lev(LAMP1);
    lamp[1] = bcm2835_gpio_lev(LAMP1);
    lamp[2] = bcm2835_gpio_lev(LAMP3);
    lamp[3] = bcm2835_gpio_lev(LAMP4);
}