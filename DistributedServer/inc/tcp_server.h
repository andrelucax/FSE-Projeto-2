#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#define MY_SERVER_PORT 10129

int init_tcp_server();
void *handle_tcp_client(void *_air_mrt);
void close_sockets();
int wait_for_client();

#endif /* _TCP_SERVER_H_ */