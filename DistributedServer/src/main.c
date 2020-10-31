#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// My libs
#include "gpio_utils.h"
#include "bme280_utils.h"
#include "data_utils.h"
#include "tcp_server.h"

void sig_handler(int signum);
void update_values();
void send_data();
void before_exit();

pthread_t thread_tcp_server;

int main(){
    printf("Handling signals...\n");
    signal(SIGALRM, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGSTOP, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGQUIT, sig_handler);
    // ualarm(1000000, 1000000);

    printf("Starting BCM...\n");
    if(init_bcm()){
        printf("Failed to start BCM\n");
        exit(-1);
    }

    printf("Starting BME280...\n");
    if (setup_bme280()){
        printf("Failed to start BME280\n");
        exit(-2);
    }

    printf("Starting TCP server...\n");
    if (init_tcp_server()){
        printf("Failed to start TCP server\n");
        exit(-3);
    }

    printf("Starting threads\n");
    if (pthread_create(&thread_tcp_server, NULL, handle_tcp_client, NULL))
    {
        printf("Fail to create TCP server thread");
        exit(-4);
    }

    printf("Running\n");

    pthread_join(thread_tcp_server, NULL);

    before_exit();

    return 0;
}

void sig_handler(int signum){
    if (signum == SIGALRM){
        // Every 1 sec
        double humidity = 0, temperature = 0;
        int presence[2], openning[6];
        update_values(&humidity, &temperature, presence, openning);
        send_data(&humidity, &temperature, presence, openning);
    }
    else{
        before_exit();
    }
}

void before_exit(){
    pthread_cancel(thread_tcp_server);
    close_sockets();

    exit(0);
}
