#include "inputwin.h"
#define ctl(w) ((w) & 0x1f)
#define ctl2(z) ((z) & 0x1f)
#define ctl3(y) ((y) & 0x1f)
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

inputwin::inputwin(WINDOW *win, int y, int x,ListaDoble *listaD,ListaSimpleOrdenada *listao,ListaSimpleOrdenada *listao2,Pila *undo,Pila *redo){
    textwin=win;
    this->locy=y;
    this->locx=x;
    this->listaD=listaD;
    this->listaO=listao;
    this->unDo=undo;
    this->reDo=redo;
    this->cadena=new ListaDoble();
    this->listaO2=listao2;
    getmaxyx(textwin,maxy,maxx);
}

int inputwin::getmv(){
    noecho();
    int choice=wgetch(textwin);

    if(choice==KEY_BACKSPACE){
        if(locx==0){
            mvwaddch(textwin,locy,locx,' ');
            locx=maxx-1;
            locy--;
            this->listaD->borrarFinal();
        }else if(locy==0 && locx==0){
            mvwaddch(textwin,locy,locx,' ');
            this->listaD->borrarFinal();
        }else{
            wmove(textwin,locy,locx);
            mvwaddch(textwin,locy,locx,' ');
            locx--;
            this->listaD->borrarFinal();
        }
    }else if(choice==KEY_F(2)){
        //mvwaddstr(textwin,20,1,"^w(Buscar y Reemplazar  ^c(Reportes)    ^s(Guardar)");
        NodoLog *temp= this->unDo->pop();
        if(temp->palabraBuscar=="NULL"){
            this->listaD->borrarFinal();
        }else{
            reemplazar(temp->palabraReemplazar,temp->palabraBuscar);
        }
        this->reDo->push(temp->palabraBuscar,temp->palabraReemplazar,true,temp->palabra,temp->pos);
        for (int var = 0; var < 75; ++var) {
            for (int i = 2; i < 17; ++i) {
                mvwaddch(textwin,i,var,' ');
            }
        }
        mvwaddstr(textwin,2,2,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
        locy=getcury(textwin); locx=getcurx(textwin);
    }else if(choice==KEY_F(3)){
        if(!this->reDo->esVacia()){
            NodoLog *temp=this->reDo->pop();
            this->unDo->push(temp->palabraBuscar,temp->palabraReemplazar,false,temp->palabra,temp->pos);
            if(temp->palabraBuscar=="NULL"){
                this->listaD->insertarFinal(temp->palabra,false);
            }else{
                reemplazar(temp->palabraReemplazar,temp->palabraBuscar);
            }
            for (int var = 0; var < 75; ++var) {
                for (int i = 0; i < 17; ++i) {
                    mvwaddch(textwin,i,var,' ');
                }
            }
        }
        mvwaddstr(textwin,0,0,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
        locy=getcury(textwin); locx=getcurx(textwin);
    }
    else if(choice==ctl('w')){

        int auxx=locx;
        int auxy=locy;
        mvwprintw(textwin,18,2,"Buscar y remplazar ");
        int auxlocx=locx=getcurx(textwin);
        int auxlocy=locy=getcury(textwin);
        int condicion=0;                        // es para parar el while
        wattron(textwin,A_REVERSE);
        do{
            noecho();
            condicion=wgetch(textwin);
            if(condicion==127){
                locx--;
                mvwaddch(textwin,locy,locx,' ');
                this->cadena->borrarFinal();
            }else{
                mvwaddch(textwin,locy,locx,condicion);
                char caracter=(char)condicion;
                this->cadena->insertarFinal(caracter,false);
                locx++;
            }
        }while (condicion!=10);
        wattroff(textwin,A_REVERSE);
        mvwaddstr(textwin,18,2,"                                                            ");
        locy=auxy;
        locx=auxx;
        wmove(textwin,locy,locx);
        if(condicion==10){
            std::string palabra;
            palabra=this->cadena->getPalabra();
            std::vector<std::string> v;
            v=split(palabra,';');
            std::string palabraBorrada,palabraNueva;
            if(!v.empty()){
                palabraBorrada=v.at(0);
                palabraNueva=v.at(1);
            }
            reemplazar(palabraBorrada,palabraNueva);
            this->unDo->push(palabraBorrada,palabraNueva,false,' ',0);
            this->listaO->insertar(palabraBorrada,palabraNueva);
            this->listaO2->insertar(palabraNueva,palabraBorrada);
            for (int var = 2; var < 73; ++var) {
                for (int i = 2; i < 17; ++i) {
                    mvwaddch(textwin,i,var,' ');
                }
            }
            palabra="";
            this->cadena->vaciar();
            v.clear();
        }

        //wrefresh(textwin);
        //mvwaddstr(textwin,17,2,this->listaD->toString().c_str());
        mvwaddstr(textwin,2,2,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
        locy=getcury(textwin); locx=getcurx(textwin);
    }else if(choice==KEY_F(4)){
        mvwaddstr(textwin,18,1,"REPORTES 1)Lista    2)Palabras Buscadas  3)Palabras Ordenadas");
        int seleccion=wgetch(textwin);
        if(seleccion=='1'){
            this->listaD->imprimirDoble();
            mvwaddstr(textwin,18,1,"                                                        ");
            wrefresh(textwin);
        }else if (seleccion=='2') {
            this->unDo->graficarUndo();
            this->reDo->graficarRedo();
            mvwaddstr(textwin,18,1,"                                                        ");
            wrefresh(textwin);
        }

    }
    else{
        if(locx==maxx-1){
            locy++;
            locx=0;

        }else
            locx++;
        mvwaddch(textwin,locy,locx,choice);
        this->listaD->insertarFinal(choice,false);
        this->unDo->push("NULL","NULL",false,choice,(locy-1)*73);
        this->reDo->vaciar();
    }

    return choice;
}

void inputwin::typing(char caracter){
    //inputwin::boublelist.insertarFinal(caracter,false);
    mvwaddch(textwin,locy,locx,caracter);
}

void inputwin::reemplazar(std::string palabra,std::string nuevapalabra){
    //std::string palabra;
    //palabra="van";
    std::string indices;                                    //esto es para separar los indices
    indices=this->listaD->buscar(palabra);
    std::replace(indices.begin(),indices.end(),';',' ');
    std::vector<int> v;
    std::stringstream ss(indices);
    int temp;
    while (ss>>temp) {
        v.push_back(temp);
    }
    for (int var = v.size()-1; var >= 0; var--) {
        int aux=v.at(var);
        this->listaD->borrarEn(aux);
        //cout<<"lo de afuera "<<aux<<endl;
        for (int i = aux+1; i < aux+palabra.size(); ++i) {
            this->listaD->borrarEn(aux);
            //cout<<"lo de adentro "<<i<<endl;
        }
    }
    //std::string nuevapalabra;
    //nuevapalabra="ChicharronConPelos";
    if(nuevapalabra.size()< palabra.size()){
        int direfencia;
        direfencia=palabra.size()-nuevapalabra.size();
        for (int var = nuevapalabra.size()-1; var >= 0; var--) {
            int aux=v.at(0);
            this->listaD->insertertarEn(aux,nuevapalabra[var],false);
        }
        for (int var = 1; var < v.size(); ++var) {
            int aux=v.at(var)-(direfencia*var);
            for (int i = nuevapalabra.size()-1; i >= 0 ; i--) {
                this->listaD->insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }else if(nuevapalabra.size()==palabra.size()){
        for (int var = 0; var < v.size(); ++var) {
            int aux=v.at(var);
            for (int i = nuevapalabra.size()-1; i >=0 ; i--) {
                this->listaD->insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }else if(nuevapalabra.size()>palabra.size()){
        int diferenciainversa;
        diferenciainversa=nuevapalabra.size()- palabra.size();
        for (int var = nuevapalabra.size()-1; var >= 0; var--) {
            int aux=v.at(0);
            this->listaD->insertertarEn(aux,nuevapalabra[var],false);
        }
        for (int var = 1; var < v.size(); ++var) {
            int aux=v.at(var)+(diferenciainversa*var);
            for (int i = nuevapalabra.size()-1; i >= 0; i--) {
                this->listaD->insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }
    v.clear();
}

std::vector<std::string> inputwin::split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}


