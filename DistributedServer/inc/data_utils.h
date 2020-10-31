#ifndef _DATA_UTILS_H_
#define _DATA_UTILS_H_

void update_values(double *humidity, double *temperature, int presence[], int openning[]);
int send_data(double *humidity, double *temperature, int presence[], int openning[]);

#endif /* _DATA_UTILS_H_ */