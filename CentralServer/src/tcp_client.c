#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tcp_client.h"

int client_socket;

int init_tcp_client() {
	struct sockaddr_in server_addr;
	unsigned short server_port;
	char *server_IP;

	server_IP = SERVER_IP;
	server_port = SERVER_PORT;

	// Criar Socket
	if((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&server_addr, 0, sizeof(server_addr)); // Zerando a estrutura de dados
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_IP);
	server_addr.sin_port = htons(server_port);

	// Connect
	if(connect(client_socket, (struct sockaddr *) &server_addr, 
							sizeof(server_addr)) < 0)
		printf("Erro no connect()\n");

	// tamanhoMensagem = strlen(mensagem);

	// if(send(client_socket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
	// 	printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	// totalBytesRecebidos = 0;
	// while(totalBytesRecebidos < tamanhoMensagem) {
	// 	if((bytesRecebidos = recv(client_socket, buffer, 16-1, 0)) <= 0)
	// 		printf("Não recebeu o total de bytes enviados\n");
	// 	totalBytesRecebidos += bytesRecebidos;
	// 	buffer[bytesRecebidos] = '\0';
	// 	printf("%s\n", buffer);
	// }
	// close(client_socket);
	// exit(0);
}

int send_message_to_server(int device_type, int device_id, int on_off){
    int is_ok = 1;
    if(send(client_socket, (void *) &device_type, sizeof(int), 0) < 0)
		is_ok = 0;

    if(send(client_socket, (void *) &device_id, sizeof(int), 0) < 0)
		is_ok = 0;

    if(send(client_socket, (void *) &on_off, sizeof(int), 0) < 0)
		is_ok = 0;

    if(recv(client_socket, (void *) &on_off, sizeof(int), 0) < 0){
        is_ok = 0;
    }

    if(!is_ok){
        return 1;
    }

    return 0;
}

void close_socket(){
	close(client_socket);
}