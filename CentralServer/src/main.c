#include <stdio.h>
#include <pthread.h>

#include "ncurses_utils.h"
#include "tcp_client.h"
#include "gpio_defines.h"

void *watch_userinput();

pthread_t thread_userinput;

int main(){
    if(init_screens()){
        return -1;
    }

    if (pthread_create(&thread_userinput, NULL, watch_userinput, NULL)){
        return -2;
    }
    
    pthread_join(thread_userinput, NULL);

    close_socket();
    finish_screens(1);

    return 0;
}

void *watch_userinput(){
    int menuOption;
    while ((menuOption = getch()) != KEY_F(1)){
        if (menuOption == KEY_F(2)){
            // Turn lamp on
            send_message_to_server(LAMP, 1, ON);
        }
        else if (menuOption == KEY_F(3)){
            // Turn lamp off
        }
        else if (menuOption == KEY_F(4)){
            // Turn air on
        }
        else if (menuOption == KEY_F(5)){
            // Turn air off
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