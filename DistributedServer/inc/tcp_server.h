#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#define SERVER_PORT 10129

int init_tcp_server();
void *handle_tcp_client();
void close_sockets();

#endif /* _TCP_SERVER_H_ */