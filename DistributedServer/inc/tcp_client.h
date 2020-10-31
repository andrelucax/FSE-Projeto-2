#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#define SERVER_IP "192.168.0.53"
#define SERVER_PORT 10029

int init_tcp_client();
int send_message_to_server(double *humidity, double *temperature, int presence[], int openning[]);
void close_socket();

#endif // _TCP_CLIENT_H_