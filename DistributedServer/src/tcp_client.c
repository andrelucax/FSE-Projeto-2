#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tcp_client.h"

int client_socket;
struct sockaddr_in server_addr;

int init_tcp_client() {
	unsigned short server_port;
	char *server_IP;

	server_IP = SERVER_IP;
	server_port = OTHER_SERVER_PORT;

	// Criar Socket
	if((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return 1;

	// Construir struct sockaddr_in
	memset(&server_addr, 0, sizeof(server_addr)); // Zerando a estrutura de dados
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_IP);
	server_addr.sin_port = htons(server_port);

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

	return 0;
}

int send_message_to_server(double *humidity, double *temperature, int presence[], int openning[], int air[], int lamp[]){
	if(init_tcp_client()){
        return 1;
    }
	// Connect
	if(connect(client_socket, (struct sockaddr *) &server_addr, 
							sizeof(server_addr)) < 0){
		return 2;
	}

    int is_ok = 0;
    if(send(client_socket, (void *) humidity, sizeof(double), 0) < 0)
		is_ok = -1;

    if(send(client_socket, (void *) temperature, sizeof(double), 0) < 0)
		is_ok = -2;

    if(send(client_socket, (void *) presence, sizeof(int)*2, 0) < 0)
		is_ok = -3;
	
	if(send(client_socket, (void *) openning, sizeof(int)*6, 0) < 0)
		is_ok = -4;

	if(send(client_socket, (void *) air, sizeof(int)*2, 0) < 0)
		is_ok = -5;

	if(send(client_socket, (void *) lamp, sizeof(int)*4, 0) < 0)
		is_ok = -6;

    if(is_ok){
        return is_ok;
    }

	close_socket();

    return 0;
}

void close_socket(){
	close(client_socket);
}