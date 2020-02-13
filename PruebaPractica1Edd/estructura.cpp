#include "estructura.h"

Estructura::Estructura(){
    this->archivoslista =new ListaCircular();
    this->caracterlista =new ListaDoble();
    this->redo=new Pila();
    this->reemplazolista =new ListaSimpleOrdenada();
    this->undo=new Pila();
}


