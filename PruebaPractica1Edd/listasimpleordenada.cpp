#include "listasimpleordenada.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

ListaSimpleOrdenada::ListaSimpleOrdenada(){
    this->primero=NULL;
    this->ultimo=NULL;
    this->size=0;
}

int ListaSimpleOrdenada::getSize(){
    return size;
}

void ListaSimpleOrdenada::insertar( std::string reemplazadoPor, std::string reemplazoA){
    NodoOrdenadas *n=new NodoOrdenadas(reemplazadoPor,reemplazoA);
    if(primero==NULL){
        primero=n;
        ultimo=n;
        size++;
    }else{
        if(strcmp(n->reemplazadoPor.c_str(),primero->reemplazadoPor.c_str())<=0){
            NodoOrdenadas *temp=primero;
            primero=n;
            n->siguiente=temp;
        }else if (strcmp(n->reemplazadoPor.c_str(),ultimo->reemplazadoPor.c_str())>=0) {
            ultimo->siguiente=n;
            ultimo=n;
        } else {
            NodoOrdenadas *aux=primero;
            NodoOrdenadas *anterior;
            while (aux!=NULL&&strcmp(aux->reemplazadoPor.c_str(),n->reemplazadoPor.c_str())<0) {
                anterior=aux;
                aux=aux->siguiente;
            }
            anterior->siguiente=n;
            n->siguiente=aux;
        }
        size++;
    }
}

std::string ListaSimpleOrdenada::toString(){
    NodoOrdenadas *temp=primero;
    std::string cadena;
    cadena="digraph G {node [shape = square]; \n graph [rankdir=LR]; \n node [color = green]; \n node [style = filled];\n";
    while (temp->siguiente!=NULL) {
        cadena+="\"["+temp->reemplazadoPor+" \\n Reemplazado a: "+temp->reemplazoA+"]\" ->";
        temp=temp->siguiente;
    }
    cadena+="\"["+temp->reemplazadoPor+" \\n Reemplazado a: "+temp->reemplazoA+"]\"}";
    return cadena;
}

std::string ListaSimpleOrdenada::toString2(){
    NodoOrdenadas *temp=primero;
    std::string cadena;
    cadena="digraph G {node [shape = square]; \n graph [rankdir=LR]; \n node [color = green]; \n node [style = filled];\n";
    while (temp->siguiente!=NULL) {
        cadena+="\"["+temp->reemplazadoPor+" \\n Reemplazado por: "+temp->reemplazoA+"]\" ->";
        temp=temp->siguiente;
    }
    cadena+="\"["+temp->reemplazadoPor+" \\n Reemplazado por: "+temp->reemplazoA+"]\"}";
    return cadena;
}

void ListaSimpleOrdenada::vaciar(){
    primero=NULL;
}

void ListaSimpleOrdenada::graficarBorradas(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/OrdenadaBuscada.dot";
    texto=toString();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot OrdenadaBuscada.dot -Tjpg -o OrdenadaBuscada.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/OrdenadaBuscada.jpg");
}

void ListaSimpleOrdenada::graficar2Reemplazadas(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/OrdenadaReemplazada.dot";
    texto=toString2();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot OrdenadaReemplazada.dot -Tjpg -o OrdenadaReemplazada.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/OrdenadaReemplazada.jpg");
}
