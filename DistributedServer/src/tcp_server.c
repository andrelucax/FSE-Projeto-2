#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tcp_server.h"
#include "gpio_utils.h"

int client_socket;
int server_socket;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

int init_tcp_server(){
	unsigned short server_port;

	server_port = SERVER_PORT;

	// Abrir Socket
	if((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        return 1;
    }

	// Montar a estrutura sockaddr_in
	memset(&server_addr, 0, sizeof(server_addr)); // Zerando a estrutura de dados
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(server_port);

	// Bind
	if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        return 2;
    }

	// Listen
	if(listen(server_socket, 10) < 0){
        return 3;
    }		

    return 0;
}

void *handle_tcp_client() {
	while(1){
		unsigned int client_len = sizeof(client_addr);
		if((client_socket = accept(server_socket, 
									(struct sockaddr *) &client_addr, 
									&client_len)) < 0){
			printf("Error on accept\n");
			return (void *) 0;
		}

		int is_ok = 1;

		int recv_size;
		int on_off, device_type, device_id;
		if((recv_size = recv(client_socket, on_off, sizeof(int), 0)) < 0){
			is_ok = 0;
		}
		if((recv_size = recv(client_socket, device_type, sizeof(int), 0)) < 0){
			is_ok = 0;
		}
		if((recv_size = recv(client_socket, device_id, sizeof(int), 0)) < 0){
			is_ok = 0;
		}

		if(is_ok){
			if(outp_device_on_off(device_type, device_id, on_off)){
				// Send FAIL 1 to client
				send(client_socket, 1, sizeof(int), 0);
			}
			else{
				// Send OK 0 to client
				send(client_socket, 0, sizeof(int), 0);
			}
		}
		else{
			// Send FAIL 2 to client
			send(client_socket, 2, sizeof(int), 0);
		}

		close(client_socket);
	}
}

void close_sockets(){
    close(server_socket);
    close(client_socket);
}