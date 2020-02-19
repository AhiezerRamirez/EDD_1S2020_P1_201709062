#include <iostream>
#include "listadoble.h"
#include "listasimpleordenada.h"
#include "listacircular.h"
#include "Pila.h"
#include "inputwin.h"
#include "newinputwin.h"
#include <estructura.h>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <ncurses.h>
#define ctl(x) ((x) & 0x1f)
using namespace std;

void pantallainput(){

        initscr();
        noecho();
        cbreak();
        WINDOW *menuwin=newwin(22,76,1,1);
        box(menuwin,0,0);
        refresh();
        mvwprintw(menuwin,1,2,"Universidad de San Carlos de Guatemala");
        mvwprintw(menuwin,2,2,"Facultad de Ingenieria");
        mvwprintw(menuwin,3,2,"Estructura de Datos");
        mvwprintw(menuwin,4,2,"Ahiezer Ramirez");
        mvwprintw(menuwin,5,2,"201709062");
        wrefresh(menuwin);
        //it is to use de arrowkeys
        keypad(menuwin,true);

        string opcions[4]={"1.Crear Archivo","2.Arbrir Archivo","3.Archivos Recientes","4.Salir"};
        int opcion,highlited=0;
        while(1){
            for (int var = 0; var < 4; ++var) {
                if(var==highlited)
                    wattron(menuwin,A_REVERSE);
                mvwprintw(menuwin,var+16,30,opcions[var].c_str());
                wattroff(menuwin,A_REVERSE);
            }
            opcion=wgetch(menuwin);
            switch (opcion) {
            case KEY_UP:
                highlited--;
                if(highlited==-1)
                    highlited=0;
                break;
            case KEY_DOWN:
                highlited++;
                if(highlited==4)
                    highlited=3;
                break;
            default:
                break;
            }
            if(opcion==10)
                break;
        }

        if(opcions[highlited]=="1.Crear Archivo"){
            //estruc->abrirInput();
            /*while (in->getmv()!=ctl('x')) {
                //in->typing(in->getmv());
                wrefresh(textwin);
            }*/

        }
        getch();
        endwin();
}

int main()
{   Estructura *estruc=new Estructura();
    initscr();
        noecho();
        cbreak();
        WINDOW *menuwin=newwin(22,76,1,1);
        box(menuwin,0,0);
        refresh();
        mvwprintw(menuwin,1,2,"Universidad de San Carlos de Guatemala");
        mvwprintw(menuwin,2,2,"Facultad de Ingenieria");
        mvwprintw(menuwin,3,2,"Estructura de Datos");
        mvwprintw(menuwin,4,2,"Ahiezer Ramirez");
        mvwprintw(menuwin,5,2,"201709062");
        wrefresh(menuwin);
        //it is to use de arrowkeys
        keypad(menuwin,true);

        string opcions[4]={"1.Crear Archivo","2.Arbrir Archivo","3.Archivos Recientes","4.Salir"};
        int opcion,highlited=0;
        while(1){
            box(menuwin,0,0);
            refresh();
            mvwprintw(menuwin,1,2,"Universidad de San Carlos de Guatemala");
            mvwprintw(menuwin,2,2,"Facultad de Ingenieria");
            mvwprintw(menuwin,3,2,"Estructura de Datos");
            mvwprintw(menuwin,4,2,"Ahiezer Ramirez");
            mvwprintw(menuwin,5,2,"201709062");
            wrefresh(menuwin);
            for (int var = 0; var < 4; ++var) {
                if(var==highlited)
                    wattron(menuwin,A_REVERSE);
                mvwprintw(menuwin,var+16,30,opcions[var].c_str());
                wattroff(menuwin,A_REVERSE);
            }
            opcion=wgetch(menuwin);
            switch (opcion) {
            case KEY_UP:
                highlited--;
                if(highlited==-1)
                    highlited=0;
                break;
            case KEY_DOWN:
                highlited++;
                if(highlited==4)
                    highlited=3;
                break;
            default:
                break;
            }
            if(opcion==10){
                if(opcions[highlited]=="1.Crear Archivo"){
                    WINDOW *textwin=newwin(22,76,0,0);
                    noecho();
                    newinputwin *in2=new newinputwin(textwin,0,0,estruc->caracterlista,estruc->buscadolista,estruc->reemplazolista,estruc->undo,estruc->redo,estruc,estruc->archivoslista);
                    //box(textwin,0,0);
                    keypad(textwin,true);
                    mvwhline(textwin,19,1,'-',139);
                    mvwaddstr(textwin,20,1,"^w(Buscar y Reemplazar  F4(Reportes)    F6(Guardar)");

                    wrefresh(textwin);
                    while (in2->getmv()!=ctl('x')) {
                        //in->typing(in->getmv());
                        wrefresh(textwin);
                    }
                    estruc->caracterlista->vaciar();
                    estruc->redo->vaciar();
                    estruc->reemplazolista->vaciar();
                    estruc->buscadolista->vaciar();
                    estruc->undo->vaciar();
                    wclear(textwin);
                    wrefresh(textwin);
                    endwin();

                }else if (opcions[highlited]=="2.Arbrir Archivo") {
                    WINDOW *openwin=newwin(22,76,0,0);
                    noecho();
                    inputwin *in2= new inputwin(openwin,18,17,estruc->caracterlista,estruc->buscadolista,estruc->reemplazolista,estruc->undo,estruc->redo,estruc,estruc->archivoslista);
                    keypad(openwin,true);
                    mvwhline(openwin,19,1,'-',139);
                    mvwaddstr(openwin,20,1,"^w(Buscar y Reemplazar  F4(Reportes)    F6(Guardar)");
                    mvwaddstr(openwin,18,1,"Ruta del texto: ");
                    wrefresh(openwin);
                    while (in2->getmv()!=ctl('x')) {
                        wrefresh(openwin);
                    }
                    estruc->caracterlista->vaciar();
                    estruc->redo->vaciar();
                    estruc->reemplazolista->vaciar();
                    estruc->buscadolista->vaciar();
                    estruc->undo->vaciar();
                    wclear(openwin);
                    estruc->archivoAbiero=false;
                    wrefresh(openwin);
                    endwin();
                }else if (opcions[highlited]=="3.Archivos Recientes") {
                    if(estruc->archivoslista->primero==NULL){

                    }else{
                        WINDOW *filewin=newwin(22,76,0,0);
                        noecho();
                        inputwin *in3= new inputwin(filewin,18,17,estruc->caracterlista,estruc->buscadolista,estruc->reemplazolista,estruc->undo,estruc->redo,estruc,estruc->archivoslista);
                        keypad(filewin,true);
                        mvwhline(filewin,19,1,'-',139);
                        mvwaddstr(filewin,20,1,"X.Generar Reporte de archivo");
                        mvwaddstr(filewin,8,0,estruc->archivoslista->imprimirPantalla().c_str());
                        mvwaddstr(filewin,1,20,"Archivos Recientes");
                        wrefresh(filewin);
                        while (in3->getmv2()!=ctl('x')) {
                            wrefresh(filewin);
                        }
                        endwin();
                    }
                }else if (opcions[highlited]=="4.Salir"){
                    wclear(menuwin);
                    int yy=0,xx=0;
                    getmaxyx(menuwin,yy,xx);
                    wattron(menuwin,A_REVERSE);
                    mvwprintw(menuwin,yy/2,xx/2,"Good Bye");
                    wattroff(menuwin,A_REVERSE);
                    wrefresh(menuwin);
                    getch();
                    break;
                }
            }else if(opcion==ctl('x')){
                wclear(menuwin);
                int yy=0,xx=0;
                getmaxyx(menuwin,yy,xx);
                wattron(menuwin,A_REVERSE);
                mvwprintw(menuwin,yy/2,xx/2,"Good Bye");
                wattroff(menuwin,A_REVERSE);
                wrefresh(menuwin);
                wclear(menuwin);
                getch();
                break;
            }
        }


        //refresh();
        //getch();
        endwin();
    return 0;

    /*ListaSimpleOrdenada lista;
    lista.insertar("hola","","");
    lista.insertar("como","","");
    lista.insertar("esta","","");
    lista.insertar("hola","","");
    lista.insertar("aaa","","");
    lista.insertar("zzz","","");
    lista.insertar("bbbb","","");
    lista.insertar("zzzzz","","");
    lista.insertar("eild","","");
    lista.insertar("eisodis","","");
    lista.insertar("aaa","","");
    lista.toString();
    lista.vaciar();
    lista.toString();
    ListaCircular listacir;
    listacir.insertar("nose.txt","");
    listacir.insertar("saber.txt","");
    listacir.insertar("esto.txt","");
    listacir.insertar("esta.txt","");
    listacir.insertar("facil.txt","");
    listacir.insertar("sacare.txt","");
    listacir.insertar("100.txt","");
    listacir.toString();
    listacir.vaciar();
    listacir.toString();

    std::string entrada="palabra qu, me envia"
                        " por que hay muchas "
                        "palabras que no se s"
                        "i van a venir pero c"
                        "omo son palabras men"
                        "os una palabra aqui "
                        "ya van como 100 letr"
                        "as qu palabras que cam"
                        "bie palabra ya saben"
                        " como es la cosa va "
                        "ustedes la cosa es asi";

    ListaDoble lista;
    Pila pil;
    for (int var = 0; var < entrada.length(); ++var) {
        lista.insertarFinal(entrada[var],false);
        pil.push("NULL","NULL",false,entrada[var],var+1);
    }

    cout << "Hello World!" << endl;
    std::string palabra;
    palabra="van";
    cout << lista.buscar(palabra)<<endl;
    std::string indices;                                    //esto es para separar los indices
    indices=lista.buscar(palabra);
    std::replace(indices.begin(),indices.end(),';',' ');
    std::vector<int> v;
    std::stringstream ss(indices);
    int temp;
    while (ss>>temp) {
        v.push_back(temp);
    }
    for (int var = v.size()-1; var >= 0; var--) {
        int aux=v.at(var);
        lista.borrarEn(aux);
        cout<<"lo de afuera "<<aux<<endl;
        for (int i = aux+1; i < aux+palabra.size(); ++i) {
            lista.borrarEn(aux);
            cout<<"lo de adentro "<<i<<endl;
        }
    }
lista.toString();
    std::string nuevapalabra;
    nuevapalabra="ChicharronConPelos";
    if(nuevapalabra.size()< palabra.size()){
        int direfencia;
        direfencia=palabra.size()-nuevapalabra.size();
        for (int var = nuevapalabra.size()-1; var >= 0; var--) {
            int aux=v.at(0);
            lista.insertertarEn(aux,nuevapalabra[var],false);
        }
        for (int var = 1; var < v.size(); ++var) {
            int aux=v.at(var)-(direfencia*var);
            for (int i = nuevapalabra.size()-1; i >= 0 ; i--) {
                lista.insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }else if(nuevapalabra.size()==palabra.size()){
        for (int var = 0; var < v.size(); ++var) {
            int aux=v.at(var);
            for (int i = nuevapalabra.size()-1; i >=0 ; i--) {
                lista.insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }else if(nuevapalabra.size()>palabra.size()){
        int diferenciainversa;
        diferenciainversa=nuevapalabra.size()- palabra.size();
        for (int var = nuevapalabra.size()-1; var >= 0; var--) {
            int aux=v.at(0);
            lista.insertertarEn(aux,nuevapalabra[var],false);
        }
        for (int var = 1; var < v.size(); ++var) {
            int aux=v.at(var)+(diferenciainversa*var);
            for (int i = nuevapalabra.size()-1; i >= 0; i--) {
                lista.insertertarEn(aux,nuevapalabra[i],false);
            }
        }
    }
std::cout<<"---------------------------------"<<std::endl;
pil.push(palabra,nuevapalabra,false,'*',0);
Pila pil2;
NodoLog *log;
log = pil.pop();
pil2.push(log->palabraBuscar,log->palabraReemplazar,true,log->palabra,log->pos);
delete log;
pil.toString();
pil2.toString();
pil.vaciar();

ofstream file;
file.open("/home/ahiezer/PruebaPractica1Edd/Texto.txt");
file<<lista.toString();
file.close();*/
    return 0;
}


