#include "menu.h"
#include "ncurse.h"

int main(){

    ncurse::init();

    printw("Hello world!");
    refresh();
    getch();
    endwin();
}
