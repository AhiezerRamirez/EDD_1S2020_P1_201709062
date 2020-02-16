#include "listacircular.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

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

std::string ListaCircular::imprimirPantalla(){
    NodoArchivo *temp=primero;
    std::string cadena="";
    int contador=1;
    while(temp!=ultimo){
        cadena+=std::to_string(contador)+"."+temp->archivo+"                    "+temp->ruta+"\n";
        temp=temp->siguiente;
        contador++;
    }
    cadena+=std::to_string(contador)+"."+temp->archivo+"                    "+temp->ruta+"\n";
    return cadena;
}

bool ListaCircular::existe(std::string ruta){
    NodoArchivo *temp=primero;
    while (temp!=ultimo) {
        if(temp->ruta==ruta)
            return true;
        temp=temp->siguiente;
    }
    return false;
}

std::string ListaCircular::toString(){
    NodoArchivo *temp=primero;
    std::string cadena;
    cadena="digraph G {node [shape = square]; \n graph [rankdir=LR]; \n node [color = green]; \n node [style = filled];\n";
    while (temp!=ultimo) {
        cadena+="\"["+temp->archivo +"\\n "+temp->ruta+"]\" ->";
        temp=temp->siguiente;
    }
    cadena+="\"["+temp->archivo +"\\n "+temp->ruta+"]\" ->";
    cadena+="\"["+temp->siguiente->archivo +"\\n "+temp->siguiente->ruta+"]\"}";
    return cadena;
}

void ListaCircular::graficarRutas(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/graficaRutas.dot";
    texto=toString();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot graficaRutas.dot -Tjpg -o graficaRutas.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/graficaRutas.jpg");
}

void ListaCircular::vaciar(){
    this->primero=NULL;
    this->ultimo=NULL;
}
