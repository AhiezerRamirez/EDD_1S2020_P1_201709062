#ifndef LISTASIMPLEORDENADA_H
#define LISTASIMPLEORDENADA_H
#include <string>

class NodoOrdenadas{
public:
    std::string encabezado;
    std::string reemplazadoPor;
    std::string reemplazoA;
    NodoOrdenadas *siguiente;
    NodoOrdenadas(std::string encabezado,std::string reemplazadoPor,std::string reemplazoA){
        this->encabezado=encabezado;
        this->reemplazadoPor = reemplazadoPor;
        this->reemplazoA=reemplazoA;
        this->siguiente;
    }
};
class ListaSimpleOrdenada
{
private:
    NodoOrdenadas *primero;
    NodoOrdenadas *ultimo;
    int size;
public:
    ListaSimpleOrdenada();
    int getSize();
    void toString();
    void insertar(std::string encabezado,std::string reemplazadoPor,std::string reemplazoA);
    void vaciar();
};

#endif // LISTASIMPLEORDENADA_H
