#include "listadoble.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

ListaDoble::ListaDoble()
{
    this->primero=NULL;
    this->ultimo=NULL;
    this->size=0;
}
ListaDoble::~ListaDoble(){
    Nodo *next;
    while (primero!=NULL) {
        next=primero->siguiente;
        delete primero;
        primero=next;
    }
}

std::string ListaDoble::imprimirPantalla(){
Nodo *temp=primero;
std::string cadena;
cadena="";
while (temp!=NULL) {
    cadena+=temp->letra;
    temp=temp->siguiente;
}
return cadena;
}

std::string ListaDoble::toString(){
    Nodo *temp=primero;
    std::string cadena;
    int contador=0;
    cadena = "digraph G {graph [rankdir=LR]; ";
    while (temp->siguiente!=NULL) {
        cadena+="\""+std::to_string(contador)+temp->letra+"\"->";
        temp=temp->siguiente;
        contador++;
    }
    cadena+="\""+std::to_string(contador)+temp->letra+"\"";
    temp=ultimo;
    while (temp->anterior!=NULL) {
        cadena+="\""+std::to_string(contador)+temp->letra+"\"->";
        temp=temp->anterior;
        contador--;
    }
    cadena+="\""+std::to_string(contador)+temp->letra+"\"";
    cadena+="}";
    return cadena;
}
void ListaDoble::insertarInicio(char caracter, bool espacio){
    Nodo *n=new Nodo(caracter,espacio);
    if(primero==NULL){
        primero=n;
        ultimo=n;
    }else{
        primero->anterior=n;
        n->siguiente=primero;
        primero=n;
    }
    size++;
}

void ListaDoble::insertarFinal(char caracter, bool espacio){
    Nodo *n=new Nodo(caracter,espacio);
    if(primero==NULL){
        primero=n;
        ultimo=n;

    }else{
        ultimo->siguiente=n;
        n->anterior=ultimo;
        ultimo=n;
    }
    size++;
}

void ListaDoble::insertertarEn(int pos, char carater, bool espacio){
    if(pos < 1 || pos > size + 1){
        return;
    }else if(pos == 1 ){
        insertarInicio(carater,espacio);
    }else if(pos==size+1){
        insertarFinal(carater,espacio);
    }else if(primero!=NULL){
        Nodo *n=new Nodo(carater,espacio);
        Nodo *temp=primero;
        for (int var = 1; var < pos; var++) {
            temp=temp->siguiente;
        }
        temp->anterior->siguiente=n;
        n->anterior=temp->anterior;
        n->siguiente=temp;
        temp->anterior=n;
        size++;
    }
}

void ListaDoble::borrarInicio(){
    if(primero->siguiente==NULL){
        primero=NULL;
        ultimo=NULL;
        size--;
    }else if(primero!=NULL){
        primero=primero->siguiente;
        delete primero->anterior;
        primero->anterior=NULL;
        size--;
    }

}

void ListaDoble::borrarEn(int pos){
    if(pos<1||pos>size){
        return;
    }else if(pos == 1){
        borrarInicio();
    }else if(pos==size){
        borrarFinal();
    }else if(primero!=NULL){
        Nodo *cur=primero;
        for (int var = 1; var < pos; var++) {
            cur=cur->siguiente;
        }
        cur->anterior->siguiente=cur->siguiente;
        cur->siguiente->anterior=cur->anterior;
        delete cur;
        size--;
    }
}

void ListaDoble::borrarFinal(){
    if(primero->siguiente==NULL){
        delete primero;
        primero=NULL;
        ultimo=NULL;
        size--;
    }else if(primero!=NULL){
        ultimo=ultimo->anterior;
        delete ultimo->siguiente;
        ultimo->siguiente=NULL;
        size--;
    }
}
std::string ListaDoble::buscar(std::string palabra){
    Nodo *temp=primero;
    int lenth=palabra.length();
    int contador=0;
    int auxcontador=0;
    int aux2contador=0;
    std::string indices="";
    while (temp!=NULL) {
        contador++;
        if(temp->letra==palabra[0]){
            aux2contador= auxcontador=contador;
            for (int var = 1; var < lenth; ++var) {
                if(temp->siguiente==NULL){
                    break;
                }
                temp=temp->siguiente;
                auxcontador++;
                if(temp==NULL){
                    break;
                }else{
                    if(temp->letra==palabra[var]){
                        if(var==lenth-1){
                            if(temp->siguiente==NULL||temp->siguiente->letra==' '){
                                indices+=std::to_string(aux2contador)+";";
                                break;
                            }
                        }
                    }else{
                        break;
                    }
                }
            }contador=auxcontador;
        }
        if(temp!=NULL)
        temp=temp->siguiente;
    }
    return indices;
}

void ListaDoble::vaciar(){
    this->primero=NULL;
    this->ultimo=NULL;
}

std::string ListaDoble::getPalabra(){
    Nodo *temp=primero;
    std::string palabra="";
    while (temp!=NULL) {
        palabra+=temp->letra;
        temp=temp->siguiente;
    }
    return palabra;
}

void ListaDoble::imprimirDoble(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ListaDoble.dot";
    texto=toString();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot ListaDoble.dot -Tjpg -o ListaDoble.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ListaDoble.jpg");
}
