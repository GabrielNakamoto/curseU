#include <iostream>
#include <ncurses.h>
#include <menu.h>

#include "nmenu.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void func(char *name);

int main()
{

	std::vector<std::string> choices = {
			"Choice 1",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Choice 5",
			"Choice 6",
			"Choice 7",
			"Exit",
	  };

	int c;
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;

	/* Initialize curses */	
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
	{
        my_items[i] = new_item(choices[i], "description");
		set_item_userptr(my_items[i], reinterpret_cast<void *>(func));
	}
	my_items[n_choices] = (ITEM *)NULL;

	/* Create menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Post the menu */
	mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES -5, 3, "test");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != 'q')
	{       switch(c)
	        {	case 'j':
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case 'k':
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			{	ITEM *cur;
				void (*p)(char *);

				cur = current_item(my_menu);
				p = reinterpret_cast<void (*)(char *)>(item_userptr(cur));
				p((char *)item_name(cur));
				pos_menu_cursor(my_menu);
				break;
			}
			break;
		}
	}
	unpost_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
	free_menu(my_menu);
	endwin();
}

void func(char *name)
{	move(20, 0);
	clrtoeol();
	mvprintw(20, 0, "Item selected is : %s", name);
}
