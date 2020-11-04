#ifndef _AIR_CONTROLLER_H_
#define _AIR_CONTROLLER_H_

#define HISTERESIS 0

struct air_mrt{
    int _air_mode;
    float _reference_temperature;
    float _temperature;
};

void *control_temperature(void *_air_mrt);

#endif // _AIR_CONTROLLER_H_