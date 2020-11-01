#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ncurses_utils.h"
#include "tcp_client.h"
#include "gpio_defines.h"
#include "tcp_server.h"

void *watch_userinput();

pthread_t thread_userinput;
pthread_t thread_tcp_server;

int main(){
    if(init_screens()){
        exit(-1);
    }

    if (pthread_create(&thread_userinput, NULL, watch_userinput, NULL)){
        exit(-2);
    }

    if (init_tcp_server()){
        exit(-3);
    }

    if (pthread_create(&thread_tcp_server, NULL, handle_tcp_client, NULL))
    {
        exit(-4);
    }

    pthread_join(thread_userinput, NULL);

    pthread_cancel(thread_tcp_server);

    close_socket();
    close_sockets();
    finish_screens(1);

    return 0;
}

void *watch_userinput(){
    int menuOption;
    while ((menuOption = getch()) != KEY_F(1)){
        if (menuOption == KEY_F(2)){
            // Turn lamp on
            int lamp_id = get_device_id(LAMP);
            if(lamp_id < 1 || lamp_id > 4){
                print_error();
                continue;
            }
            int server_return = send_message_to_server(LAMP, lamp_id, ON);
            if(server_return){
                if(server_return == 0) show_debug_msg("0");
                if(server_return == 1) show_debug_msg("1");
                if(server_return == 2) show_debug_msg("2");
                if(server_return == 3) show_debug_msg("3");
                if(server_return == 4) show_debug_msg("4");
                print_error();
            }
        }
        else if (menuOption == KEY_F(3)){
            // Turn lamp off
            int lamp_id = get_device_id(LAMP);
            if(lamp_id < 1 || lamp_id > 4){
                print_error();
                continue;
            }
            int server_return = send_message_to_server(LAMP, lamp_id, OFF);
            if(server_return){
                print_error();
            }
        }
        else if (menuOption == KEY_F(4)){
            // Turn air on
            int air_id = get_device_id(AIR);
            if(air_id < 1 || air_id > 2){
                print_error();
                continue;
            }
            int server_return = send_message_to_server(AIR, air_id, ON);
            if(server_return){
                print_error();
            }
        }
        else if (menuOption == KEY_F(5)){
            // Turn air off
            int air_id = get_device_id(AIR);
            if(air_id < 1 || air_id > 2){
                print_error();
                continue;
            }
            int server_return = send_message_to_server(AIR, air_id, OFF);
            if(server_return){
                print_error();
            }
        }
        else if (menuOption == KEY_F(6)){
            // Activate alarm
        }
        else if (menuOption == KEY_F(7)){
            // Deactivate alarm
        }
    }

    return 0;
}