#ifndef NEWnewinputwin_H
#define NEWnewinputwin_H
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

class newinputwin
{
public:
    ListaDoble *listaD,*cadena,*cadenaPaGuardar,*listaPaAbrir;
    ListaSimpleOrdenada *listaO,*listaO2;
    Pila *unDo,*reDo;
    ListaCircular *listarutas;
    newinputwin(WINDOW *win,int y, int x,ListaDoble *listad,ListaSimpleOrdenada *listao,ListaSimpleOrdenada *listao2,Pila *undo,Pila *redo,Estructura *estructura,ListaCircular *listarutas);
    int getmv();
    int getmv2();
    void typing(char caracter);
    void reemplazar(std::string palabra,std::string nuevapalabra);
    std::vector<std::string> split(std::string strToSplit, char delimeter);
    //ListaDoble boublelist;

    int locy,locx,maxy,maxx;
    char character;
    Estructura *estructura;
    WINDOW *textwin;
};

#endif // NEWnewinputwin_H
