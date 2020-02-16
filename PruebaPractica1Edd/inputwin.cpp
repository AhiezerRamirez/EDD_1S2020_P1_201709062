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

inputwin::inputwin(WINDOW *win, int y, int x,ListaDoble *listaD,ListaSimpleOrdenada *listao,ListaSimpleOrdenada *listao2,Pila *undo,Pila *redo,Estructura *estructura,ListaCircular *listarutas){
    textwin=win;
    this->locy=y;
    this->locx=x;
    this->listaD=listaD;
    this->listaO=listao;
    this->unDo=undo;
    this->reDo=redo;
    this->cadena=new ListaDoble();
    this->cadenaPaGuardar=new ListaDoble();
    this->listaPaAbrir=new ListaDoble();
    this->listaO2=listao2;
    this->estructura=estructura;
    this->listarutas=listarutas;
    getmaxyx(textwin,maxy,maxx);
}

int inputwin::getmv(){
    noecho();
    //locy=getcurx(textwin);
    //locx=getcury(textwin);
    int choice=wgetch(textwin);

    if(choice==KEY_BACKSPACE){
        if(locx==0){
            mvwaddch(textwin,locy,locx,' ');
            locx=maxx-1;
            locy--;
            this->unDo->push("NULL","NULL",false,this->listaD->ultimo->letra,(locy*73)+locx,true);
            this->listaD->borrarFinal();
        }else if(locy==0 && locx==0){
            mvwaddch(textwin,locy,locx,' ');
            this->unDo->push("NULL","NULL",false,this->listaD->ultimo->letra,(locy*73)+locx,true);
            this->listaD->borrarFinal();
        }else{

            mvwaddch(textwin,locy,locx,' ');
            locx--;
            wmove(textwin,locy,locx);
            this->unDo->push("NULL","NULL",false,this->listaD->ultimo->letra,(locy*73)+locx,true);
            this->listaD->borrarFinal();
        }
    }else if(choice==KEY_F(2)){
        //mvwaddstr(textwin,20,1,"^w(Buscar y Reemplazar  ^c(Reportes)    ^s(Guardar)");
        if(!unDo->esVacia()){
            NodoLog *temp= this->unDo->pop();
            if(temp->palabraBuscar=="NULL"){
                if(temp->borrado==false){
                    this->listaD->borrarFinal();
                }else{
                    this->listaD->insertarFinal(temp->palabra,false);
                }

            }else{
                reemplazar(temp->palabraReemplazar,temp->palabraBuscar);
            }
            this->reDo->push(temp->palabraBuscar,temp->palabraReemplazar,true,temp->palabra,temp->pos,temp->borrado);
            for (int var = 0; var < 75; ++var) {
                for (int i = 0; i < 17; ++i) {
                    mvwaddch(textwin,i,var,' ');
                }
            }
        }
        mvwaddstr(textwin,0,0,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
        locy=getcury(textwin); locx=getcurx(textwin);
    }else if(choice==KEY_F(3)){
        if(!this->reDo->esVacia()){
            NodoLog *temp=this->reDo->pop();
            this->unDo->push(temp->palabraBuscar,temp->palabraReemplazar,false,temp->palabra,temp->pos,temp->borrado);
            if(temp->palabraBuscar=="NULL"){
                if(temp->borrado==false){
                    this->listaD->insertarFinal(temp->palabra,false);
                }else{
                    this->listaD->borrarFinal();
                }

            }else{
                reemplazar(temp->palabraBuscar,temp->palabraReemplazar);
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
            }else if(condicion==10){

            }else{
                mvwaddch(textwin,locy,locx,condicion);
                char caracter=(char)condicion;
                this->cadena->insertarFinal(caracter,false);
                locx++;
            }
        }while (condicion!=10);
        wattroff(textwin,A_REVERSE);
        mvwaddstr(textwin,18,2,"                                                                      ");
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
            this->listaO->insertar(palabraBorrada,palabraNueva);
            this->listaO2->insertar(palabraNueva,palabraBorrada);
            this->unDo->push(palabraBorrada,palabraNueva,false,' ',0,false);
            for (int var = 0; var < 73; ++var) {
                for (int i = 0; i < 17; ++i) {
                    mvwaddch(textwin,i,var,' ');
                }
            }
            palabra="";
            this->cadena->vaciar();
            v.clear();
        }

        //wrefresh(textwin);
        //mvwaddstr(textwin,17,2,this->listaD->toString().c_str());
        mvwaddstr(textwin,0,0,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
        locy=getcury(textwin); locx=getcurx(textwin);
    }else if(choice==KEY_F(4)){
        mvwaddstr(textwin,18,1,"REPORTES 1)Lista    2)Palabras Buscadas  3)Palabras Ordenadas");
        int seleccion=wgetch(textwin);
        if(seleccion=='1'){
            this->listaD->imprimirDoble();                  //Esta marranada es para graficar no para imprimir
            mvwaddstr(textwin,18,1,"                                                           ");
            wrefresh(textwin);
        }else if (seleccion=='2') {
            this->unDo->graficarUndo();
            this->reDo->graficarRedo();
            mvwaddstr(textwin,18,1,"                                                             ");
            wrefresh(textwin);
        }else if(seleccion=='3'){
            this->listaO->graficarBorradas();
            this->listaO2->graficar2Reemplazadas();
            mvwaddstr(textwin,18,1,"                                                             ");
            wrefresh(textwin);
        }

    }else if(choice==KEY_F(5)){
        for (int var = 0; var < 75; ++var) {
            for (int i = 0; i < 17; ++i) {
                mvwaddch(textwin,i,var,' ');
            }
        }
        if(this->listaD->getSize()!=0)
            mvwaddstr(textwin,0,0,this->listaD->imprimirPantalla().c_str());
        wrefresh(textwin);
    }else if(choice==KEY_F(6)){
        mvwaddstr(textwin,18,1,"Nombre: ");
        wrefresh(textwin);
        int auxx=locx;
        int auxy=locy;
        int selc=0;
        locy=18;locx=9;
        //selc=wgetch(textwin);
        do{
            selc=wgetch(textwin);
            if(selc!=10){
                this->cadenaPaGuardar->insertarFinal(selc,false);
                mvwaddch(textwin,locy,locx,selc);
                wrefresh(textwin);
                locx++;
            }
        }while (selc!=10);

        this->listaD->guardarTXT(this->cadenaPaGuardar->imprimirPantalla());
        mvwaddstr(textwin,18,1,"                                ");
        wrefresh(textwin);
        locy=auxy;locx=auxx;
        wmove(textwin,locy,locx);
        wrefresh(textwin);
        this->cadenaPaGuardar->vaciar();
    }else if (choice==10) {

    }
    else{
        if(estructura->archivoAbiero==true){
            if(locx==maxx-1){
                locy++;
                locx=0;

            }else
                locx++;
            mvwaddch(textwin,locy,locx,choice);
            this->listaD->insertarFinal(choice,false);
            this->unDo->push("NULL","NULL",false,choice,(locy+1)*73,false);
            this->reDo->vaciar();
        }else{
            this->listaPaAbrir->vaciar();
            //mvwaddch(textwin,locy,locx,choice);
            //this->listaPaAbrir->insertarFinal(choice,false);
            //locx++;
            int op;op=0;
            //op=wgetch(textwin);
            do{
                op=wgetch(textwin);
                if(op!=KEY_ENTER){
                    mvwaddch(textwin,locy,locx,op);
                    this->listaPaAbrir->insertarFinal(op,false);
                    locx++;
                    wrefresh(textwin);
                }

            }while(op!=10 );
            if(op==10){
                std::string ruta="";
                this->listaPaAbrir->borrarFinal();
                ruta = this->listaPaAbrir->imprimirPantalla();
                std::ifstream myfile (ruta.c_str());
                wrefresh(textwin);
                char eacChar;
                //myfile.open(ruta.c_str());
                  if (myfile.is_open())
                  {
                      while (!myfile.eof()) {
                          myfile.get(eacChar);
                          this->listaD->insertarFinal(eacChar,false);
                      }
                      if(!this->listarutas->existe(ruta.substr(ruta.find_last_of("/") + 1)))
                        this->listarutas->insertar(ruta.substr(ruta.find_last_of("/") + 1),ruta);
                      myfile.close();
                  }
                  this->listaD->borrarFinal();
                  mvwaddstr(textwin,18,1,"                                           ");
                  mvwaddstr(textwin,0,0,this->listaD->imprimirPantalla().c_str());
                  wrefresh(textwin);
                  locy=getcury(textwin); locx=getcurx(textwin);
            }

            wrefresh(textwin);
            estructura->archivoAbiero=true;
        }
    }

    return choice;
}

int inputwin::getmv2(){
    int opcion;
    opcion=wgetch(textwin);
    if(opcion=='x'){
        this->listarutas->graficarRutas();
    }
    return opcion;
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
    if(!v.empty()){
        for (int var = v.size()-1; var >= 0; var--) {
            if(!v.empty()){
                int aux=v.at(var);
                this->listaD->borrarEn(aux);
                //cout<<"lo de afuera "<<aux<<endl;
                for (int i = aux+1; i < aux+palabra.size(); ++i) {
                    this->listaD->borrarEn(aux);
                    //cout<<"lo de adentro "<<i<<endl;
                }
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
    }
    indices="";
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


