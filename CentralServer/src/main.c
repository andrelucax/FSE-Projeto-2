#include "ncurses_utils.h"

#include <stdio.h>

int main(){
    if(init_screens()){
        return -1;
    }

    getchar();

    finish_screens(1);

    return 0;
}