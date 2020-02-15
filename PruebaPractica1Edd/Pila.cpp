#include "Pila.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

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

void Pila::push(std::string palabrabuscar, std::string palabraReemplazar, bool estado, char palabra, int pos,bool borrado){
    NodoLog *n=new NodoLog(palabrabuscar,palabraReemplazar,estado,palabra,pos,borrado);
    if(top==NULL){
        top=n;
    }else{
        n->siguiente=top;
        top=n;
    }
}

NodoLog* Pila::peek(){
    if(top!=NULL)
        return top;
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

std::string Pila::toString(){
    NodoLog *temp;
    temp=top;
    std::string cadena;
    cadena="digraph G {node [shape = square]; \n graph [rankdir=LR]; \n node [color = green]; \n node [style = filled];\n";
    int contador=0;
    while (temp->siguiente!=NULL) {
        cadena+="\""+std::to_string(contador)+"[PalabraBuscada:"+temp->palabraBuscar+"\\n PalabraAReemplazar:"+
                temp->palabraReemplazar+"\\n Revertido:"+
                std::to_string(temp->estado)+"\\n Palabra:"+
                std::to_string(temp->palabra)+"\\n Posicion:"+
                std::to_string(temp->pos)+"]\" ->";
        temp=temp->siguiente;
        contador++;
    }
    cadena+="\""+std::to_string(contador)+"[PalabraBuscada:"+temp->palabraBuscar+"\\n PalabraAReemplazar:"+
            temp->palabraReemplazar+"\\n Revertido:"+
            std::to_string(temp->estado)+"\\n Palabra:"+
            std::to_string(temp->palabra)+"\\n Posicion:"+
            std::to_string(temp->pos)+"]\"";
    cadena+="}";
    return cadena;
}

std::string Pila::toString2(){
    NodoLog *temp;
    temp=top;
    std::string cadena;
    cadena="digraph G {node [shape = square]; \n graph [rankdir=LR]; \n node [color = red]; \n node [style = filled];\n";
    int contador=0;
    while (temp->siguiente!=NULL) {
        cadena+="\""+std::to_string(contador)+"PalabraBuscada:"+temp->palabraBuscar+" \\n PalabraAReemplazar:"+
                temp->palabraReemplazar+"\\n Revertido:"+
                std::to_string(temp->estado)+"\\n Palabra:"+
                std::to_string((char)temp->palabra)+"\\n Posicion:"+
                std::to_string(temp->pos)+"\" ->";
        temp=temp->siguiente;
        contador++;
    }
    cadena+="\""+std::to_string(contador)+"PalabraBuscada:"+temp->palabraBuscar+"\\n PalabraAReemplazar:"+
            temp->palabraReemplazar+"\\n Revertido:"+
            std::to_string(temp->estado)+"\\n Palabra:"+
            std::to_string((char)temp->palabra)+"\\n Posicion:"+
            std::to_string(temp->pos)+"\"";
    cadena+="}";
    return cadena;
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
bool Pila::esVacia(){
    if(top==NULL)
        return true;
    else
        return false;
}

void Pila::graficarUndo(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/Undo.dot";
    texto=toString();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot Undo.dot -Tjpg -o Undo.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/Undo.jpg");
}

void Pila::graficarRedo(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/Redo.dot";
    texto=toString2();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot Redo.dot -Tjpg -o Redo.jpg");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("xdg-open /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/Redo.jpg");
}
