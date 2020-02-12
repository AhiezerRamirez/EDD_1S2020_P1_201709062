#include "Pila.h"
#include <iostream>

Pila::Pila(){
    this->top=NULL;
}
Pila::~Pila(){
    NodoLog *temp;
    temp=top;
    while (temp!=NULL) {
        temp=top->siguiente;
        delete top;
        top=temp;
    }
}

void Pila::push(std::string palabrabuscar, std::string palabraReemplazar, bool estado, char palabra, int pos){
    NodoLog *n=new NodoLog(palabrabuscar,palabraReemplazar,estado,palabra,pos);
    if(top==NULL){
        top=n;
    }else{
        n->siguiente=top;
        top=n;
    }
}

NodoLog* Pila::pop(){
    if(top==NULL)
        return NULL;
    else{
        NodoLog *temp;
        temp=top;
        top=top->siguiente;
        return temp;
    }
}

void Pila::toString(){
    NodoLog *temp;
    temp=top;
    while (temp!=NULL) {
        std::cout<<temp->palabraBuscar<<" "<<temp->palabraReemplazar<<temp->estado<<" "<<temp->palabra<<" "<<temp->pos<< std::endl;
        temp=temp->siguiente;
    }
}
void Pila::vaciar(){
    NodoLog *temp;
    temp=top;
    while (temp!=NULL) {
        temp=top->siguiente;
        delete top;
        top=temp;
    }
    top=NULL;
}
