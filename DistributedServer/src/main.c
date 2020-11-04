#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// My libs
#include "gpio_utils.h"
#include "bme280_utils.h"
#include "data_utils.h"
#include "tcp_server.h"
#include "air_controller.h"

void sig_handler(int signum);
void before_exit();
void *handle_send_data();

pthread_t thread_tcp_server;
pthread_t thread_tcp_client;
pthread_t thread_air_controller;

sem_t sem_send_data;

int main(){
    printf("Handling signals...\n");
    signal(SIGALRM, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGSTOP, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGQUIT, sig_handler);
    alarm(1);

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

    printf("Starting threads...\n");
    struct air_mrt _air_mrt;
    _air_mrt._air_mode = AIR;
    if (pthread_create(&thread_tcp_server, NULL, handle_tcp_client, (void *) &_air_mrt)){
        printf("Failed to create TCP server thread\n");
        exit(-4);
    }

    sem_init(&sem_send_data, 0, 0);
    if (pthread_create(&thread_tcp_client, NULL, handle_send_data, (void *) &_air_mrt)){
        printf("Failed to create TCP server thread\n");
        exit(-4);
    }

    if (pthread_create(&thread_air_controller, NULL, control_temperature, (void *) &_air_mrt)){
        printf("Failed to create air controller thread\n");
        exit(-4);
    }

    pthread_join(thread_tcp_server, NULL);

    before_exit();

    return 0;
}

void *handle_send_data(void * _air_mrt){
    struct air_mrt *m_air_mrt = (struct air_mrt *) _air_mrt;
    while(1){
        sem_wait(&sem_send_data);
        double humidity = 0, temperature = 0;
        int presence[2], openning[6], air[2], lamp[4];
        printf("Updating values...\n");
        update_values(&humidity, &temperature, presence, openning, air, lamp);

        m_air_mrt->_temperature = temperature;

        printf("Sending data...\n");
        if (send_data(&humidity, &temperature, presence, openning, air, lamp)){
            printf("Failed to send data\n");
        }
    }
}

void sig_handler(int signum){
    if (signum == SIGALRM){
        // Every 1 sec
        alarm(1);
        sem_post(&sem_send_data);
    }
    else{
        before_exit();
    }
}

void before_exit(){
    pthread_cancel(thread_tcp_server);
    pthread_cancel(thread_air_controller);
    close_sockets();

    exit(0);
}
