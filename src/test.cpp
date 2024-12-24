#include <iostream>
#include "menu.h"
#include <ncurses.h>
#include <menu.h>

int main()
{
	int c;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

    std::vector<std::string> choices = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit"
    };

    ncurse::Menu menu(choices);

	mvprintw(LINES - 2, 0, "F1 to Exit");
	post_menu(menu.getHandle());
	refresh();

	while((c = getch()) != 'q')
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(menu.getHandle(), REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu.getHandle(), REQ_UP_ITEM);
				break;
		}
	}

	endwin();
}

