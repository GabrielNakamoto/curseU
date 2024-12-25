#pragma once

#include "common.h"

namespace csru
{

class Window
{
private:

    Handle<WINDOW> handle;

    int height, width, starty, startx;

public:

    Window(int height, int width, int starty, int startx)
        :   height(height)
        ,   width(width)
        ,   starty(starty)
        ,   startx(startx)
        ,   handle(newwin(height, width, starty, startx),
                   [&](WINDOW *win){
                        delwin(win);
                   })
    {

    }

};

}
