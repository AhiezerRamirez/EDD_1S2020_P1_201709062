#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <string>

class NodoArchivo
{
public:
    NodoArchivo *siguiente;
    std::string archivo;
    std::string ruta;
    NodoArchivo(std::string archivo, std::string ruta) {
        this->archivo=archivo;
        this->ruta=ruta;
        this->siguiente=NULL;
    }
};

class ListaCircular
{
    NodoArchivo *primero;
    NodoArchivo *ultimo;
    int size;
public:
    ListaCircular();
    void insertar(std::string archivo,std::string ruta);
    std::string toString();
    void vaciar();
};

#endif // LISTACIRCULAR_H
