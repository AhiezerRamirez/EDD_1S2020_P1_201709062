#include "estructura.h"

Estructura::Estructura(){
    this->archivoslista =new ListaCircular();
    this->caracterlista =new ListaDoble();
    this->redo=new Pila();
    this->reemplazolista =new ListaSimpleOrdenada();
    this->undo=new Pila();
    this->buscadolista=new ListaSimpleOrdenada();
}

void Estructura::imprimirDoble(){
    std::string texto,ruta;
    ruta="/home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ListaCircular.dot";
    texto=this->caracterlista->toString();
    std::ofstream fileCitas;
    fileCitas.open(ruta.c_str());
    fileCitas<<texto;
    fileCitas.close();
    system("cd /home/ahiezer/Practica1Edd20/PruebaPractica1Edd/ && dot ListaCircular.dot -Tjpg -o ListaCircular.jpg");
}

