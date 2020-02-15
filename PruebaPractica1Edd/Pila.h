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
    bool borrado;
    NodoLog(std::string palabrabuscar,std::string palabraReemplazar,bool estado,char palabra,int pos,bool borrado){
        this->palabraBuscar=palabrabuscar;
        this->palabraReemplazar=palabraReemplazar;
        this->estado=estado;
        this->palabra=palabra;
        this->pos=pos;
        this->siguiente=NULL;
        this->borrado=borrado;
    }
};

class Pila
{
public:
    Pila();
    ~Pila();
    NodoLog *top;
    void push(std::string palabrabuscar,std::string palabraReemplazar,bool estado,char palabra,int pos,bool borrado);
    NodoLog* pop();
    NodoLog* peek();
    std::string toString();
    std::string toString2();
    void graficarUndo();
    void graficarRedo();
    bool esVacia();
    void vaciar();
};

#endif // NODOLOG_H
