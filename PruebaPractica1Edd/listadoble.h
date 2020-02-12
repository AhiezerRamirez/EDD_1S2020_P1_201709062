#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include <iostream>
#include <string>
#include <string.h>

class Nodo
{
public:
    char letra;
    bool espacio;
    Nodo *siguiente;
    Nodo *anterior;
    Nodo(char letra,bool espacio) {
        this->letra=letra;
        this->espacio=espacio;
        this->siguiente=NULL;
        this->anterior=NULL;
    }
};

class ListaDoble
{
private:
    Nodo *primero;
    Nodo *ultimo;
    int size;
public:
    ListaDoble();
    ~ListaDoble();
    int getSize();
    std::string toString();
    void insertarFinal(char caracter,bool espacio);
    void insertertarEn(int pos,char carater,bool espacio);
    void insertarInicio(char caracter,bool espacio);
    void borrarInicio();
    void borrarFinal();
    void borrarEn(int pos);
    std::string buscar(std::string palabra);
};

#endif // LISTADOBLE_H
