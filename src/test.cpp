#include <iostream>
#include "menu.h"
#include "crsu.h"
#include <ncurses.h>
#include <menu.h>

int main()
{

	int c;

    crsu::init();

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

    crsu::Menu menu(choices);

    menu.display();
	refresh();

	while((c = getch()) != 'q')
	{
        switch(c)
	    {	case 'k':
                menu.selectUp();
				break;
			case 'j':
                menu.selectDown();
				break;
		}
	}

	endwin();
}

