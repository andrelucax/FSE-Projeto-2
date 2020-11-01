#ifndef _GPIO_UTILS_H_
#define _GPIO_UTILS_H_

#include <bcm2835.h>

#define ON 1
#define OFF 0

#define LAMP 0
#define AIR 1
#define PRESENCE 2
#define OPENNING 3

#define LAMP1 RPI_V2_GPIO_P1_11 // KITCHEN
#define LAMP2 RPI_V2_GPIO_P1_12 // LIVING ROOM
#define LAMP3 RPI_V2_GPIO_P1_13 // BEDROOM 1
#define LAMP4 RPI_V2_GPIO_P1_15 // BEDROOM 2
#define AIR1 RPI_V2_GPIO_P1_16 // BEDROOM 1
#define AIR2 RPI_V2_GPIO_P1_18 // BEDROOM 2
#define PRESENCE1 RPI_V2_GPIO_P1_22 // LIVING ROOM
#define PRESENCE2 RPI_V2_GPIO_P1_37 // KITCHEN
#define OPENNING1 RPI_V2_GPIO_P1_29 // KITCHEN DOOR
#define OPENNING2 RPI_V2_GPIO_P1_31 // KITCHEN WINDOW
#define OPENNING3 RPI_V2_GPIO_P1_32 // LIVING ROOM DOOR
#define OPENNING4 RPI_V2_GPIO_P1_36 // LIVING ROOM WINDOW
#define OPENNING5 RPI_V2_GPIO_P1_38 // BEDROOM 1 WINDOW
#define OPENNING6 RPI_V2_GPIO_P1_40 // BEDROOM 2 WINDOW

int init_bcm();
int outp_device_on_off(int device_type, int device_id, int on_off);
void get_inpt_device_on_off(int presence[], int openning[]);
void get_outp_device_on_off(int lamp[], int air[]);

#endif /* _GPIO_UTILS_H_ */