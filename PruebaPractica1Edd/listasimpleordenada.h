#ifndef LISTASIMPLEORDENADA_H
#define LISTASIMPLEORDENADA_H
#include <string>

class NodoOrdenadas{
public:
    std::string reemplazadoPor;
    std::string reemplazoA;
    NodoOrdenadas *siguiente;
    NodoOrdenadas(std::string reemplazadoPor,std::string reemplazoA){
        this->reemplazadoPor = reemplazadoPor;
        this->reemplazoA=reemplazoA;
        this->siguiente=NULL;
    }
};
class ListaSimpleOrdenada
{

public:
    ListaSimpleOrdenada();
    int getSize();
    std::string toString();
    std::string toString2();
    void insertar(std::string reemplazadoPor,std::string reemplazoA);
    void vaciar();
    void graficarBorradas();
    void graficar2Reemplazadas();
    NodoOrdenadas *primero;
    NodoOrdenadas *ultimo;
    int size;
};

#endif // LISTASIMPLEORDENADA_H
