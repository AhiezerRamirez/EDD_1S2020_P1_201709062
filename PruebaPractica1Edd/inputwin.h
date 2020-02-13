#ifndef INPUTWIN_H
#define INPUTWIN_H
#include <ncurses.h>
#include "listadoble.h"
#include "listasimpleordenada.h"
#include "Pila.h"
#include <string>
#include <string.h>
class inputwin
{
public:
    ListaDoble *listaD;
    ListaSimpleOrdenada *listaO;
    Pila *unDo,*reDo;
    inputwin(WINDOW *win,int y, int x,ListaDoble *listad,ListaSimpleOrdenada *listao,Pila *undo,Pila *redo);
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
