#include <ncurses_utils.h>
#include <string.h>
#include <float.h>

#include "gpio_defines.h"

WINDOW *menuWindow;
WINDOW *menuBoxWindow;

WINDOW *inputWindow;
WINDOW *inputBoxWindow;

WINDOW *dataWindow;
WINDOW *dataBoxWindow;

int init_screens()
{
    initscr();            // Init curses mode
    noecho();             // Don't need to see user input
    cbreak();             // Disable line buffering, gimme every thing
    keypad(stdscr, TRUE); // Gimme that spicy F button
    curs_set(0);          // Hide cursor
    refresh();

    int row, col;
    getmaxyx(stdscr, row, col);
    if (row < 31 || col < 120)
    {
        endwin();

        printf("Screen too small, min rows = 31 and min columns = 120\n\rGot rows = %d and columns = %d\n\rPlease resize your screen\n", row, col);

        return -1;
    }

    menuWindow = create_newwin(LINES - 3, COLS / 2, 0, 0, 0);
    menuBoxWindow = create_newwin(LINES - 3, COLS / 2, 0, 0, 1);

    inputWindow = create_newwin(3, COLS / 2, LINES - 3, 0, 0);
    inputBoxWindow = create_newwin(3, COLS / 2, LINES - 3, 0, 1);

    dataWindow = create_newwin(LINES, COLS / 2, 0, COLS / 2, 0);
    dataBoxWindow = create_newwin(LINES, COLS / 2, 0, COLS / 2, 1);

    print_menu();
    print_waiting_for_client();

    return 0;
}

void finish_screens(int goodbye)
{
    delwin(menuBoxWindow);
    delwin(menuWindow);

    delwin(inputWindow);
    delwin(inputBoxWindow);

    delwin(dataWindow);
    delwin(dataBoxWindow);

    if (goodbye)
    {
        messageGoodBye();
        getch();
    }
    endwin();
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int bbox)
{
    if (!bbox)
    {
        height -= 2;
        width -= 2;
        starty += 1;
        startx += 1;
    }

    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);

    if (bbox)
    {
        box(local_win, 0, 0);
    }

    wrefresh(local_win);

    return local_win;
}

void messageGoodBye()
{
    clear();
    char byeMsg[] = "Good bye! Have a nice day!";
    char exitMsg[] = "Press any button to exit";
    mvprintw(LINES / 2 - 1, COLS / 2 - strlen(byeMsg) / 2, byeMsg);
    mvprintw(LINES / 2, COLS / 2 - strlen(exitMsg) / 2, exitMsg);
}

void print_menu()
{
    wclear(menuWindow);

    mvwprintw(menuWindow, 0, 0, "Option F1: exit program");
    mvwprintw(menuWindow, 2, 0, "Option F2: turn lamp on");
    mvwprintw(menuWindow, 3, 0, "Option F3: turn lamp off");
    mvwprintw(menuWindow, 4, 0, "Option F4: turn air on");
    mvwprintw(menuWindow, 5, 0, "Option F5: turn air off");
    mvwprintw(menuWindow, 6, 0, "Option F6: activate alarm");
    mvwprintw(menuWindow, 7, 0, "Option F7: deactivate alarm");

    wrefresh(menuWindow);
}

void print_waiting_for_client(){
    wclear(dataWindow);
    mvwprintw(dataWindow, 0, 0, "Waiting for client");
    wrefresh(dataWindow);
}

void print_error(){
    wclear(inputWindow);

    mvwprintw(inputWindow, 0, 0, "Error on command");

    wrefresh(inputWindow);
}

int get_device_id(int device_type){
    echo();

    wclear(inputWindow);

    int device_id = 0;
    if(device_type == LAMP){
        mvwprintw(inputWindow, 0, 0, "Enter lamp id > ");
    }
    else if(device_type == AIR){
        mvwprintw(inputWindow, 0, 0, "Enter air id > ");
    }
    else{
        return 0;
    }

    wrefresh(inputWindow);
    wscanw(inputWindow, "%d", &device_id);

    wclear(inputWindow);
    wrefresh(inputWindow);

    noecho();

    return device_id;
}

void update_values(double temperature, double humidity, int presence[], int openning[], int air[], int lamp[]){
    if(temperature > 0.0 && temperature < 100.0)
        mvwprintw(dataWindow, 0 , 0, "Temperature: ----------- %.2lf         ", temperature);
    if(humidity > 0.0 && humidity < 100.0) 
        mvwprintw(dataWindow, 1 , 0, "Humidity: -------------- %.2lf         ", humidity);

    if(lamp[0] == ON)
        mvwprintw(dataWindow, 3 , 0, "Kitchen lamp (id 1): --- ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Kitchen lamp (id 1): --- OFF           ");
    if(lamp[1] == ON)
        mvwprintw(dataWindow, 3 , 0, "Living room lamp (id 2): ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Living room lamp (id 2): OFF           ");
    if(lamp[1] == ON)
        mvwprintw(dataWindow, 3 , 0, "Bedroom 1 lamp (id 3): - ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Bedroom 1 lamp (id 3): - OFF           ");
    if(lamp[1] == ON)
        mvwprintw(dataWindow, 3 , 0, "Bedroom 2 lamp (id 4): - ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Bedroom 2 lamp (id 4): - OFF           ");
    
    if(air[0] == ON)
        mvwprintw(dataWindow, 3 , 0, "Bedroom 1 air (id 1): -- ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Bedroom 1 air (id 1): -- OFF           ");
    if(air[1] == ON)
        mvwprintw(dataWindow, 3 , 0, "Bedroom 2 air (id 2): -- ON            ");
    else
        mvwprintw(dataWindow, 3 , 0, "Bedroom 2 air (id 2): -- OFF           ");

    if(presence[0] == ON)
        mvwprintw(dataWindow, 3 , 0, "Presence living room: -- Detected      ");
    else if(presence[0] == OFF)
        mvwprintw(dataWindow, 3 , 0, "Presence living room: -- Nothing       ");
    if(presence[1] == ON)
        mvwprintw(dataWindow, 4 , 0, "Presence kitchen: ------ Detected      ");
    
    else if(presence[1] == OFF)
        mvwprintw(dataWindow, 4 , 0, "Presence kitchen: ------ Nothing       ");
    if(openning[0] == ON)
        mvwprintw(dataWindow, 6 , 0, "Kitchen door: ---------- Detected      ");
    else if(openning[0] == OFF)
        mvwprintw(dataWindow, 6 , 0, "Kitchen door: ---------- Nothing       ");
    if(openning[1] == ON)
        mvwprintw(dataWindow, 7 , 0, "Kitchen window: -------- Detected      ");
    else if(openning[1] == OFF)
        mvwprintw(dataWindow, 7 , 0, "Kitchen window: -------- Nothing       ");
    if(openning[2] == ON)
        mvwprintw(dataWindow, 8 , 0, "Living room door: ------ Detected      ");
    else if(openning[2] == OFF)
        mvwprintw(dataWindow, 8 , 0, "Living room door: ------ Nothing       ");
    if(openning[3] == ON)
        mvwprintw(dataWindow, 9 , 0, "Living room window: ---- Detected      ");
    else if(openning[3] == OFF)
        mvwprintw(dataWindow, 9 , 0, "Living room window: ---- Nothing       ");
    if(openning[4] == ON)
        mvwprintw(dataWindow, 10, 0, "Bedroom 1 window: ------ Detected      ");
    else if(openning[4] == OFF)
        mvwprintw(dataWindow, 10, 0, "Bedroom 1 window: ------ Nothing       ");
    if(openning[5] == ON)
        mvwprintw(dataWindow, 11, 0, "Bedroom 2 window: ------ Detected      ");
    else if(openning[5] == OFF)
        mvwprintw(dataWindow, 11, 0, "Bedroom 2 window: ------ Nothing       ");

    wrefresh(dataWindow);
}
