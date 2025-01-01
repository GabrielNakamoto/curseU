#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <memory>
#include <vector>

#include <ncurses.h>
#include <menu.h>

#include "handle.h"

namespace crsu {

enum class Req
{
	DownItem = REQ_DOWN_ITEM,
	LeftItem = REQ_LEFT_ITEM,
	RightItem = REQ_RIGHT_ITEM,
	UpItem = REQ_UP_ITEM,
	ToggleItem = REQ_TOGGLE_ITEM,
	FirstItem = REQ_FIRST_ITEM,
	LastItem = REQ_LAST_ITEM,
	NextItem = REQ_NEXT_ITEM,
	PrevItem = REQ_PREV_ITEM,
	ScrUline = REQ_SCR_ULINE,
	ScrDline = REQ_SCR_DLINE,
	ScrDpage = REQ_SCR_DPAGE,
	ScrUpage = REQ_SCR_UPAGE,
	ClearPattern = REQ_CLEAR_PATTERN,
	BackPattern = REQ_BACK_PATTERN,
	NextMatch = REQ_NEXT_MATCH,
	PrevMatch = REQ_PREV_MATCH
};


class Menu
{
private:

    // vector of Item handles?

    Handle<ITEM*> itemsHandle;
    Handle<MENU> handle;

    ITEM **allocateItems(const std::vector<std::string> &itemNames)
    {
        size_t n = itemNames.size();
        ITEM **items = new ITEM*[n + 1];

        for (int i=0; i<n; ++i)
        {
            items[i] = new_item(itemNames[i].c_str(), "");
        }
        items[n] = static_cast<ITEM*>(NULL);

        return items;
    }

public:

    // free menu disconnects it from item array

    Menu(const std::vector<std::string> &itemNames)
        :   itemsHandle(allocateItems(itemNames),
                        [&](ITEM **items)
                        {
                            for (int i=0; i<itemNames.size(); ++i)
                            {
                                free_item(items[i]);
                            }
                        })
        ,   handle(new_menu(itemsHandle.get()), free_menu)
    {

    }

    ~Menu()
    {

    }

    // wrap this?
    ITEM *currentItem() const noexcept
    {
        return current_item(handle.get());
    }

    void display() const noexcept
    {
        post_menu(handle.get());
    }

	void driver(Req request) const noexcept
	{
		menu_driver(handle.get(), static_cast<int>(request));
	}
};

}

#endif
