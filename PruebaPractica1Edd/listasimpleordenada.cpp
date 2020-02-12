#include "listasimpleordenada.h"
#include <string.h>
#include <iostream>

ListaSimpleOrdenada::ListaSimpleOrdenada(){
    this->primero=NULL;
    this->ultimo=NULL;
    this->size=0;
}

int ListaSimpleOrdenada::getSize(){
    return size;
}

void ListaSimpleOrdenada::insertar(std::string encabezado, std::string reemplazadoPor, std::string reemplazoA){
    NodoOrdenadas *n=new NodoOrdenadas(encabezado,reemplazadoPor,reemplazoA);
    if(primero==NULL){
        primero=n;
        ultimo=n;
        size++;
    }else{
        if(strcmp(n->encabezado.c_str(),primero->encabezado.c_str())<=0){
            NodoOrdenadas *temp=primero;
            primero=n;
            n->siguiente=temp;
        }else if (strcmp(n->encabezado.c_str(),ultimo->encabezado.c_str())>=0) {
            ultimo->siguiente=n;
            ultimo=n;
        } else {
            NodoOrdenadas *aux=primero;
            NodoOrdenadas *anterior;
            while (aux!=NULL&&strcmp(aux->encabezado.c_str(),n->encabezado.c_str())<0) {
                anterior=aux;
                aux=aux->siguiente;
            }
            anterior->siguiente=n;
            n->siguiente=aux;
        }
        size++;
    }
}

void ListaSimpleOrdenada::toString(){
    NodoOrdenadas *temp=primero;
    while (temp!=NULL) {
        std::cout<<temp->encabezado<<" ";
        temp=temp->siguiente;
    }
    std::cout<<std::endl;
}
void ListaSimpleOrdenada::vaciar(){
    primero=NULL;
}
