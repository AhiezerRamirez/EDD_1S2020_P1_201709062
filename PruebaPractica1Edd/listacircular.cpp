#include "listacircular.h"
#include <iostream>

ListaCircular::ListaCircular()
{
    this->primero=NULL;
    this->ultimo=NULL;
    this->size=0;
}

void ListaCircular::insertar(std::string archivo, std::string ruta){
    NodoArchivo *n=new NodoArchivo(archivo,ruta);
    if(primero==NULL){
        primero=n;
        ultimo=n;
        ultimo->siguiente=primero;
        size++;
    }else{
        ultimo->siguiente=n;
        ultimo=n;
        n->siguiente=primero;
    }
}

std::string ListaCircular::toString(){
    NodoArchivo *temp=primero;
    while (temp!=ultimo) {
        std::cout<<temp->archivo<<std::endl;
        temp=temp->siguiente;
    }
    std::cout<<temp->archivo<<std::endl;
    return "o";
}

void ListaCircular::vaciar(){
    this->primero=NULL;
    this->ultimo=NULL;
}
