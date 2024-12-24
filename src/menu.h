#pragma once

#include "handle.h"
#include "common.h"

namespace ncurse {

class Item
{
private:

    std::string name;
    std::string description;

    Handle<ITEM> handle;

public:

    Item(const std::string &name, const std::string &description)
        :   name(name)
        ,   description(description)
        ,   handle(new_item(name.c_str(), description.c_str()),
                    [](ITEM *item){
                        free_item(item);
                    })
    {

    }

    [[nodiscard]] const std::string &getName() const noexcept
    {
        return name;
    }

    [[nodiscard]] const std::string &getDescription() const noexcept
    {
        return description;
    }

};

class Menu
{
private:

    Handle<ITEM*> itemsHandle;
    Handle<MENU> handle;

public:

    MENU *getHandle()
    {
        return handle.get();
    }

    Menu(const std::vector<std::string> &itemNames)
        :   itemsHandle([&]()->ITEM**
                        {
                            size_t n = itemNames.size();
                            ITEM **items = new ITEM*[n + 1];
                            for (int i=0; i<n; ++i)
                            {
                                items[i] = new_item(itemNames[i].c_str(), "");
                            }
                            items[n] = static_cast<ITEM*>(NULL);
                            return items;
                        }(),
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
};

}
