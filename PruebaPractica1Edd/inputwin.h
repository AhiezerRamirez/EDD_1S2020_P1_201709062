#ifndef INPUTWIN_H
#define INPUTWIN_H
#include <ncurses.h>
#include "listadoble.h"
#include "listasimpleordenada.h"
#include "Pila.h"
#include "estructura.h"
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <iostream>

class inputwin
{
public:
    ListaDoble *listaD,*cadena,*cadenaPaGuardar,*listaPaAbrir;
    ListaSimpleOrdenada *listaO,*listaO2;
    Pila *unDo,*reDo;
    inputwin(WINDOW *win,int y, int x,ListaDoble *listad,ListaSimpleOrdenada *listao,ListaSimpleOrdenada *listao2,Pila *undo,Pila *redo,Estructura *estructura);
    int getmv();
    void typing(char caracter);
    void reemplazar(std::string palabra,std::string nuevapalabra);
    std::vector<std::string> split(std::string strToSplit, char delimeter);
    //ListaDoble boublelist;
private:
    int locy,locx,maxy,maxx;
    char character;
    Estructura *estructura;
    WINDOW *textwin;

};

#endif // INPUTWIN_H
