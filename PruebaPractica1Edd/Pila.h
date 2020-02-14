#ifndef NODOLOG_H
#define NODOLOG_H
#include <iostream>
#include <string>

class NodoLog
{
    public:
    NodoLog *siguiente;
    std::string palabraBuscar;
    std::string palabraReemplazar;
    bool estado;
    char palabra;
    int pos;
    NodoLog(std::string palabrabuscar,std::string palabraReemplazar,bool estado,char palabra,int pos){
        this->palabraBuscar=palabrabuscar;
        this->palabraReemplazar=palabraReemplazar;
        this->estado=estado;
        this->palabra=palabra;
        this->pos=pos;
        this->siguiente=NULL;
    }
};

class Pila
{
public:
    Pila();
    ~Pila();
    NodoLog *top;
    void push(std::string palabrabuscar,std::string palabraReemplazar,bool estado,char palabra,int pos);
    NodoLog* pop();
    std::string toString();
    std::string toString2();
    void graficarUndo();
    void graficarRedo();
    bool esVacia();
    void vaciar();
};

#endif // NODOLOG_H
