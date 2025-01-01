#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <memory>
#include <vector>

#include <ncurses.h>
#include <menu.h>

#include "handle.h"

namespace crsu {

class Menu
{
private:

    // vector of Item handles?

    Handle<ITEM*> itemsHandle;
    /* std::vector<H> */
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
        ,   handle(new_menu(itemsHandle.get()),
                       [](MENU *menu)
                      {
                            free_menu(menu);
                       })
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

    void selectLeft() const noexcept
    {
        menu_driver(handle.get(), REQ_LEFT_ITEM);
    }

    void selectRight() const noexcept
    {
        menu_driver(handle.get(), REQ_LEFT_ITEM);
    }

    void selectUp() const noexcept
    {
        menu_driver(handle.get(), REQ_UP_ITEM);
    }

    void selectDown() const noexcept
    {
        menu_driver(handle.get(), REQ_DOWN_ITEM);
    }

};

}

#endif