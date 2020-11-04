#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ncurses_utils.h"
#include "tcp_client.h"
#include "gpio_defines.h"
#include "tcp_server.h"
#include "log.h"

void *watch_userinput();

pthread_t thread_userinput;
pthread_t thread_tcp_server;

int alarm = 0;

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

    if (pthread_create(&thread_tcp_server, NULL, handle_tcp_client, (void *) &alarm))
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
                save_in_log("Turn lamp on", "Failed (invalid ID)");
                print_error();
                continue;
            }
            int server_return = send_message_to_server(LAMP, lamp_id, ON);
            if(server_return){
                save_in_log("Turn lamp on", "Failed (server)");
                print_error();
            }
            else{
                save_in_log("Turn lamp on", "Ok");
            }
        }
        else if (menuOption == KEY_F(3)){
            // Turn lamp off
            int lamp_id = get_device_id(LAMP);
            if(lamp_id < 1 || lamp_id > 4){
                save_in_log("Turn lamp off", "Failed (invalid ID)");
                print_error();
                continue;
            }
            int server_return = send_message_to_server(LAMP, lamp_id, OFF);
            if(server_return){
                save_in_log("Turn lamp off", "Failed (server)");
                print_error();
            }
            else{
                print_air_status("# Air status: Manual                             ");
                save_in_log("Turn lamp off", "Ok");
            }
        }
        else if (menuOption == KEY_F(4)){
            // Turn air on
            int air_id = get_device_id(AIR);
            if(air_id < 1 || air_id > 2){
                save_in_log("Turn air on", "Failed (invalid ID)");
                print_error();
                continue;
            }
            int server_return = send_message_to_server(AIR, air_id, ON);
            if(server_return){
                save_in_log("Turn air on", "Failed (server)");
                print_error();
            }
            else{
                print_air_status("# Air status: Manual                             ");
                save_in_log("Turn air on", "Ok");
            }
        }
        else if (menuOption == KEY_F(5)){
            // Turn air off
            int air_id = get_device_id(AIR);
            if(air_id < 1 || air_id > 2){
                save_in_log("Turn air off", "Failed (invalid ID)");
                print_error();
                continue;
            }
            int server_return = send_message_to_server(AIR, air_id, OFF);
            if(server_return){
                save_in_log("Turn air off", "Failed (server)");
                print_error();
            }
            else{
                save_in_log("Turn air off", "Ok");
            }
        }
        else if(menuOption == KEY_F(6)){
            // Define air temperature
            float air_temperature = get_temperature();
            if(air_temperature < 0.0f || air_temperature > 100.0f){
                save_in_log("Define temperature", "Failed (bad temperature)");
                print_error();
                continue;
            }
            int server_return = send_message_to_server_f(TEMPERATURE, air_temperature);
            if(server_return){
                save_in_log("Define temperature", "Failed (server)");
                print_error();
            }
            else{
                char msg_air_status[50] = "";
                sprintf(msg_air_status, "# Air status: Auto, reference: %.2f     ", air_temperature);
                print_air_status(msg_air_status);
                save_in_log("Define temperature", "Ok");
            }
        }
        else if (menuOption == KEY_F(7)){
            alarm = 1;
            clear_input();
            save_in_log("Turn alarm on", "Ok");
        }
        else if (menuOption == KEY_F(8)){
            alarm = 0;
            clear_input();
            save_in_log("Turn alarm off", "Ok");
        }
    }

    return 0;
}