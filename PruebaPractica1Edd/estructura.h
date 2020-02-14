#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H
#include <ncurses.h>
#include <string>
#include <fstream>
#include "listadoble.h"
#include "listasimpleordenada.h"
#include "listacircular.h"
#include "Pila.h"

class Estructura
{
public:
    ListaDoble *caracterlista;
    ListaSimpleOrdenada *reemplazolista,*buscadolista;
    ListaCircular *archivoslista;
    Pila *undo,*redo;
    Estructura();
    void imprimirDoble();
};

#endif // ESTRUCTURA_H
