#ifndef _NCURSES_UTILS_H_
#define _NCURSES_UTILS_H_

#include <ncurses.h>

int init_screens();
void finish_screens(int goodbye);
WINDOW *create_newwin(int height, int width, int starty, int startx, int bbox);
void messageGoodBye();
void print_menu();
void print_error();
int get_device_id(int device_type);
void print_waiting_for_client();
void update_t_h(double temperature, double humidity);
void update_presence(int presence[]);
void update_openning(int openning[]);

#endif /* _NCURSES_UTILS_H_ */