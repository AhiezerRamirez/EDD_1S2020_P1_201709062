#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H
#include <ncurses.h>
#include <string>
#include "listadoble.h"
#include "listasimpleordenada.h"
#include "listacircular.h"
#include "Pila.h"

class Estructura
{
public:
    ListaDoble *caracterlista;
    ListaSimpleOrdenada *reemplazolista;
    ListaCircular *archivoslista;
    Pila *undo,*redo;
    Estructura();
};

#endif // ESTRUCTURA_H
