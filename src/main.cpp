#include <ncurses.h>
#include <menu.h>
#include <iostream>

#include "nmenu.h"
#include "crsu.h"

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
		{
			case 'k':
				menu.driver(crsu::Req::UpItem);
				break;
			case 'j':
				menu.driver(crsu::Req::DownItem);
				break;
		}
	}

	endwin();
}


