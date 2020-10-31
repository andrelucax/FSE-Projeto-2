#include <ncurses_utils.h>
#include <string.h>
#include <float.h>

#include "gpio_defines.h"

WINDOW *menuWindow;
WINDOW *menuBoxWindow;

WINDOW *inputWindow;
WINDOW *inputBoxWindow;

WINDOW *sensorhtWindow;
WINDOW *sensorhtBoxWindow;

WINDOW *lamp1Window;
WINDOW *lamp1BoxWindow;
WINDOW *lamp2Window;
WINDOW *lamp2BoxWindow;
WINDOW *lamp3Window;
WINDOW *lamp3BoxWindow;
WINDOW *lamp4Window;
WINDOW *lamp4BoxWindow;

WINDOW *air1Window;
WINDOW *air1BoxWindow;
WINDOW *air2Window;
WINDOW *air2BoxWindow;

WINDOW *presenceSensor1Window;
WINDOW *presenceSensor1BoxWindow;
WINDOW *presenceSensor2Window;
WINDOW *presenceSensor2BoxWindow;

WINDOW *openning1Window;
WINDOW *openning1BoxWindow;
WINDOW *openning2Window;
WINDOW *openning2BoxWindow;
WINDOW *openning3Window;
WINDOW *openning3BoxWindow;
WINDOW *openning4Window;
WINDOW *openning4BoxWindow;
WINDOW *openning5Window;
WINDOW *openning5BoxWindow;
WINDOW *openning6Window;
WINDOW *openning6BoxWindow;

WINDOW *alarmWindow;
WINDOW *alarmBoxWindow;

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

    sensorhtWindow = create_newwin(5, COLS / 2, 0, COLS / 2, 0);
    sensorhtBoxWindow = create_newwin(5, COLS / 2, 0, COLS / 2, 1);

    lamp1Window = create_newwin(3, COLS / 4, 5, COLS / 2, 0);
    lamp1BoxWindow = create_newwin(3, COLS / 4, 5, COLS / 2, 1);
    lamp2Window = create_newwin(3, COLS / 4 - 1, 5, COLS / 4 * 3 + 1, 0);
    lamp2BoxWindow = create_newwin(3, COLS / 4 - 1, 5, COLS / 4 * 3 + 1, 1);
    lamp3Window = create_newwin(3, COLS / 4, 8, COLS / 2, 0);
    lamp3BoxWindow = create_newwin(3, COLS / 4, 8, COLS / 2, 1);
    lamp4Window = create_newwin(3, COLS / 4 - 1, 8, COLS / 4 * 3 + 1, 0);
    lamp4BoxWindow = create_newwin(3, COLS / 4 - 1, 8, COLS / 4 * 3 + 1, 1);

    air1Window = create_newwin(3, COLS / 4, 11, COLS / 2, 0);
    air1BoxWindow = create_newwin(3, COLS / 4, 11, COLS / 2, 1);
    air2Window = create_newwin(3, COLS / 4 - 1, 11, COLS / 4 * 3 + 1, 0);
    air2BoxWindow = create_newwin(3, COLS / 4 - 1, 11, COLS / 4 * 3 + 1, 1);

    presenceSensor1Window = create_newwin(3, COLS / 4, 14, COLS / 2, 0);
    presenceSensor1BoxWindow = create_newwin(3, COLS / 4, 14, COLS / 2, 1);
    presenceSensor2Window = create_newwin(3, COLS / 4 - 1, 14, COLS / 4 * 3 + 1, 0);
    presenceSensor2BoxWindow = create_newwin(3, COLS / 4 - 1, 14, COLS / 4 * 3 + 1, 1);

    openning1Window = create_newwin(3, COLS / 4, 17, COLS / 2, 0);
    openning1BoxWindow = create_newwin(3, COLS / 4, 17, COLS / 2, 1);
    openning2Window = create_newwin(3, COLS / 4 - 1, 17, COLS / 4 * 3 + 1, 0);
    openning2BoxWindow = create_newwin(3, COLS / 4 - 1, 17, COLS / 4 * 3 + 1, 1);
    openning3Window = create_newwin(3, COLS / 4, 20, COLS / 2, 0);
    openning3BoxWindow = create_newwin(3, COLS / 4, 20, COLS / 2, 1);
    openning4Window = create_newwin(3, COLS / 4 - 1, 20, COLS / 4 * 3 + 1, 0);
    openning4BoxWindow = create_newwin(3, COLS / 4 - 1, 20, COLS / 4 * 3 + 1, 1);
    openning5Window = create_newwin(3, COLS / 4, 23, COLS / 2, 0);
    openning5BoxWindow = create_newwin(3, COLS / 4, 23, COLS / 2, 1);
    openning6Window = create_newwin(3, COLS / 4 - 1, 23, COLS / 4 * 3 + 1, 0);
    openning6BoxWindow = create_newwin(3, COLS / 4 - 1, 23, COLS / 4 * 3 + 1, 1);

    alarmWindow = create_newwin(LINES - 26, COLS / 2, 26, COLS / 2, 0);
    alarmBoxWindow = create_newwin(LINES - 26, COLS / 2, 26, COLS / 2, 1);

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

    delwin(sensorhtWindow);
    delwin(sensorhtBoxWindow);

    delwin(lamp1Window);
    delwin(lamp1BoxWindow);
    delwin(lamp2Window);
    delwin(lamp2BoxWindow);
    delwin(lamp3Window);
    delwin(lamp3BoxWindow);
    delwin(lamp4Window);
    delwin(lamp4BoxWindow);

    delwin(air1Window);
    delwin(air1BoxWindow);
    delwin(air2Window);
    delwin(air2BoxWindow);

    delwin(presenceSensor1Window);
    delwin(presenceSensor1BoxWindow);
    delwin(presenceSensor2Window);
    delwin(presenceSensor2BoxWindow);

    delwin(openning1Window);
    delwin(openning1BoxWindow);
    delwin(openning2Window);
    delwin(openning2BoxWindow);
    delwin(openning3Window);
    delwin(openning3BoxWindow);
    delwin(openning4Window);
    delwin(openning4BoxWindow);
    delwin(openning5Window);
    delwin(openning5BoxWindow);
    delwin(openning6Window);
    delwin(openning6BoxWindow);

    delwin(alarmWindow);
    delwin(alarmBoxWindow);

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
    wclear(sensorhtWindow);
    wclear(lamp1Window);
    wclear(lamp2Window);
    wclear(lamp3Window);
    wclear(lamp4Window);
    wclear(air1Window);
    wclear(air2Window);
    wclear(presenceSensor1Window);
    wclear(presenceSensor2Window);
    wclear(openning1Window);
    wclear(openning2Window);
    wclear(openning3Window);
    wclear(openning4Window);
    wclear(openning5Window);
    wclear(openning6Window);
    mvwprintw(sensorhtWindow, 0, 0, "Waiting for client");
    mvwprintw(lamp1Window, 0, 0, "Waiting for client");
    mvwprintw(lamp2Window, 0, 0, "Waiting for client");
    mvwprintw(lamp3Window, 0, 0, "Waiting for client");
    mvwprintw(lamp4Window, 0, 0, "Waiting for client");
    mvwprintw(air1Window, 0, 0, "Waiting for client");
    mvwprintw(air2Window, 0, 0, "Waiting for client");
    mvwprintw(presenceSensor1Window, 0, 0, "Waiting for client");
    mvwprintw(presenceSensor2Window, 0, 0, "Waiting for client");
    mvwprintw(openning1Window, 0, 0, "Waiting for client");
    mvwprintw(openning2Window, 0, 0, "Waiting for client");
    mvwprintw(openning3Window, 0, 0, "Waiting for client");
    mvwprintw(openning4Window, 0, 0, "Waiting for client");
    mvwprintw(openning5Window, 0, 0, "Waiting for client");
    mvwprintw(openning6Window, 0, 0, "Waiting for client");
    wrefresh(sensorhtWindow);
    wrefresh(lamp1Window);
    wrefresh(lamp2Window);
    wrefresh(lamp3Window);
    wrefresh(lamp4Window);
    wrefresh(air1Window);
    wrefresh(air2Window);
    wrefresh(presenceSensor1Window);
    wrefresh(presenceSensor2Window);
    wrefresh(openning1Window);
    wrefresh(openning2Window);
    wrefresh(openning3Window);
    wrefresh(openning4Window);
    wrefresh(openning5Window);
    wrefresh(openning6Window);
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

    noecho();

    return device_id;
}
