#include <ncurses_utils.h>
#include <string.h>
#include <float.h>

WINDOW *menuWindow;
WINDOW *menuBoxWindow;

WINDOW *inputWindow;
WINDOW *inputBoxWindow;

WINDOW *room1Window;
WINDOW *room1BoxWindow;
WINDOW *room2Window;
WINDOW *room2BoxWindow;

WINDOW *lamp1Window;
WINDOW *lamp1BoxWindow;
WINDOW *lamp2Window;
WINDOW *lamp2BoxWindow;
WINDOW *lamp3Window;
WINDOW *lamp3BoxWindow;
WINDOW *lamp4Window;
WINDOW *lamp4BoxWindow;
WINDOW *lamp5Window;
WINDOW *lamp5BoxWindow;
WINDOW *lamp6Window;
WINDOW *lamp6BoxWindow;

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

    room1Window = create_newwin(5, COLS / 2, 0, COLS / 2, 0);
    room1BoxWindow = create_newwin(5, COLS / 2, 0, COLS / 2, 1);
    room2Window = create_newwin(5, COLS / 2, 5, COLS / 2, 0);
    room2BoxWindow = create_newwin(5, COLS / 2, 5, COLS / 2, 1);

    lamp1Window = create_newwin(3, COLS / 4, 10, COLS / 2, 0);
    lamp1BoxWindow = create_newwin(3, COLS / 4, 10, COLS / 2, 1);
    lamp2Window = create_newwin(3, COLS / 4 - 1, 10, COLS / 4 * 3 + 1, 0);
    lamp2BoxWindow = create_newwin(3, COLS / 4 - 1, 10, COLS / 4 * 3 + 1, 1);
    lamp3Window = create_newwin(3, COLS / 4, 13, COLS / 2, 0);
    lamp3BoxWindow = create_newwin(3, COLS / 4, 13, COLS / 2, 1);
    lamp4Window = create_newwin(3, COLS / 4 - 1, 13, COLS / 4 * 3 + 1, 0);
    lamp4BoxWindow = create_newwin(3, COLS / 4 - 1, 13, COLS / 4 * 3 + 1, 1);

    presenceSensor1Window = create_newwin(3, COLS / 4, 16, COLS / 2, 0);
    presenceSensor1BoxWindow = create_newwin(3, COLS / 4, 16, COLS / 2, 1);
    presenceSensor2Window = create_newwin(3, COLS / 4 - 1, 16, COLS / 4 * 3 + 1, 0);
    presenceSensor2BoxWindow = create_newwin(3, COLS / 4 - 1, 16, COLS / 4 * 3 + 1, 1);

    openning1Window = create_newwin(3, COLS / 4, 19, COLS / 2, 0);
    openning1BoxWindow = create_newwin(3, COLS / 4, 19, COLS / 2, 1);
    openning2Window = create_newwin(3, COLS / 4 - 1, 19, COLS / 4 * 3 + 1, 0);
    openning2BoxWindow = create_newwin(3, COLS / 4 - 1, 19, COLS / 4 * 3 + 1, 1);
    openning3Window = create_newwin(3, COLS / 4, 22, COLS / 2, 0);
    openning3BoxWindow = create_newwin(3, COLS / 4, 22, COLS / 2, 1);
    openning4Window = create_newwin(3, COLS / 4 - 1, 22, COLS / 4 * 3 + 1, 0);
    openning4BoxWindow = create_newwin(3, COLS / 4 - 1, 22, COLS / 4 * 3 + 1, 1);
    openning5Window = create_newwin(3, COLS / 4, 25, COLS / 2, 0);
    openning5BoxWindow = create_newwin(3, COLS / 4, 25, COLS / 2, 1);
    openning6Window = create_newwin(3, COLS / 4 - 1, 25, COLS / 4 * 3 + 1, 0);
    openning6BoxWindow = create_newwin(3, COLS / 4 - 1, 25, COLS / 4 * 3 + 1, 1);

    alarmWindow = create_newwin(LINES - 28, COLS / 2, 28, COLS / 2, 0);
    alarmBoxWindow = create_newwin(LINES - 28, COLS / 2, 28, COLS / 2, 1);

    print_menu();

    return 0;
}

void finish_screens(int goodbye)
{
    delwin(menuBoxWindow);
    delwin(menuWindow);

    delwin(inputWindow);
    delwin(inputBoxWindow);

    delwin(room1Window);
    delwin(room1BoxWindow);
    delwin(room2Window);
    delwin(room2BoxWindow);

    delwin(lamp1Window);
    delwin(lamp1BoxWindow);
    delwin(lamp2Window);
    delwin(lamp2BoxWindow);
    delwin(lamp3Window);
    delwin(lamp3BoxWindow);
    delwin(lamp4Window);
    delwin(lamp4BoxWindow);
    delwin(lamp5Window);
    delwin(lamp5BoxWindow);
    delwin(lamp6Window);
    delwin(lamp6BoxWindow);

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

// void get_input_temperature(double *new_referencetemperature)
// {
//     echo();

//     wclear(inputWindow);

//     mvwprintw(inputWindow, 0, 0, "Type new reference temperature > ");

//     wscanw(inputWindow, "%lf", new_referencetemperature);

//     noecho();

//     wclear(inputWindow);

//     wrefresh(inputWindow);
// }

// void get_input_histeresis(double *new_histeresis)
// {
//     echo();

//     wclear(inputWindow);

//     mvwprintw(inputWindow, 0, 0, "Type new histeresis temperature > ");

//     wscanw(inputWindow, "%lf", new_histeresis);

//     noecho();

//     wclear(inputWindow);

//     wrefresh(inputWindow);
// }

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

// void print_messages(char message1[], char message2[], char message3[])
// {
//     wclear(messageWindow);

//     mvwprintw(messageWindow, 0, 0, message1);
//     mvwprintw(messageWindow, 1, 0, message2);
//     mvwprintw(messageWindow, 2, 0, message3);

//     wrefresh(messageWindow);
// }

// void update_messages(int mode, double referencetemperature, double histeresis)
// {
//     char str_referencetemperature[500] = "* To set mode: F2 or F3 (see options above)";
//     char str_histeresis[500] = "* To set histeresis: F4";

//     if (referencetemperature != DBL_MAX)
//     {
//         char newstr_reference_temperature[500] = "";
//         sprintf(newstr_reference_temperature, "Reference temperature: %.2lf", referencetemperature);
//         strcpy(str_referencetemperature, newstr_reference_temperature);
//     }
//     if (histeresis != DBL_MAX)
//     {
//         char newstr_histeresis[500] = "";
//         sprintf(newstr_histeresis, "Histeresis: %.2lf", histeresis);
//         strcpy(str_histeresis, newstr_histeresis);
//     }

//     if (mode == 0)
//     {
//         print_messages("To start the app please select mode and histeresis", str_referencetemperature, str_histeresis);
//     }
//     else if (mode == 1)
//     {
//         print_messages("Type: potenciometer", str_referencetemperature, str_histeresis);
//     }
//     else if (mode == 2)
//     {
//         print_messages("Type: keyboard input", str_referencetemperature, str_histeresis);
//     }
// }

// void print_sensors_data(char str_to_print[])
// {
//     wmove(sensorsDataWindow, nextLineSensorsData, 0);
//     wclrtoeol(sensorsDataWindow);
//     wrefresh(sensorsDataWindow);

//     mvwprintw(sensorsDataWindow, nextLineSensorsData, 0, str_to_print);
//     wrefresh(sensorsDataWindow);

//     if (nextLineSensorsData == LINES - 2)
//     {
//         nextLineSensorsData = 0;
//         wmove(sensorsDataWindow, nextLineSensorsData, 0);
//         wclrtoeol(sensorsDataWindow);
//         wrefresh(sensorsDataWindow);
//     }
//     else
//     {
//         wmove(sensorsDataWindow, nextLineSensorsData + 1, 0);
//         wclrtoeol(sensorsDataWindow);
//         wrefresh(sensorsDataWindow);
//         nextLineSensorsData++;
//     }
// }