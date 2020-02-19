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
    public:
    NodoArchivo *primero;
    NodoArchivo *ultimo;
    int size;

    ListaCircular();
    void insertar(std::string archivo,std::string ruta);
    std::string toString();
    std::string imprimirPantalla();
    void vaciar();
    void graficarRutas();
    bool existe(std::string archivo);
};

#endif // LISTACIRCULAR_H
