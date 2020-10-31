#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#define SERVER_IP "192.168.0.52"
#define SERVER_PORT 10129

int init_tcp_client();
int send_message_to_server(int device_type, int device_id, int on_off);
void close_socket();

#endif // _TCP_CLIENT_H_