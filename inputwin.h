#ifndef INPUTWIN_H
#define INPUTWIN_H
#include <ncurses.h>
class inputwin
{
public:

    inputwin(WINDOW *win,int y, int x);
    int getmv();
    void typing(char caracter);
private:
    int locy,locx,maxy,maxx;
    char character;
    WINDOW *textwin;
};

#endif // INPUTWIN_H
