#ifndef INPUTWIN_H
#define INPUTWIN_H
#include <ncurses.h>
#include "listadoble.h"
#include <string>
#include <string.h>
class inputwin
{
public:

    inputwin(WINDOW *win,int y, int x);
    int getmv();
    void typing(char caracter);
    void reemplazar(std::string palabra,std::string nueva);
    ListaDoble boublelist;
private:
    int locy,locx,maxy,maxx;
    char character;
    WINDOW *textwin;
};

#endif // INPUTWIN_H
