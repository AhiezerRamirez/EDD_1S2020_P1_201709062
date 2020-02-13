#include "inputwin.h"
#define ctl(w) ((w) & 0x1f)
#define ctl2(s) ((s) & 0x1f)
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>

inputwin::inputwin(WINDOW *win, int y, int x,ListaDoble *listaD,ListaSimpleOrdenada *listao,Pila *undo,Pila *redo){
    textwin=win;
    this->locy=y;
    this->locx=x;
    this->listaD=listaD;
    this->listaO=listao;
    this->unDo=undo;
    this->reDo=redo;
    getmaxyx(textwin,maxy,maxx);
}

int inputwin::getmv(){
    noecho();
    int choice=wgetch(textwin);

    if(choice==127){
        if(locx==2){
            mvwaddch(textwin,locy,locx,' ');
            locx=maxx-2;
            locy--;
        }else if(locy==2 && locx==2){
            mvwaddch(textwin,locy,locx,' ');
        }else{

            wmove(textwin,locy,locx);
            mvwaddch(textwin,locy,locx,' ');
            locx--;
        }
    }else if(choice==10){
        locx=2;
        locy++;
    }else if(choice==ctl('w')){
        std::string palabras="";
        int auxx=locx;
        int auxy=locy;
        mvwprintw(textwin,18,2,"Buscar y remplazar ");
        int auxlocx=locx=getcurx(textwin);
        int auxlocy=locy=getcury(textwin);
        int condicion=0;                        // es para parar el while
        wattron(textwin,A_REVERSE);
        do{
            condicion=wgetch(textwin);
            if(condicion==127){
                locx--;
                mvwaddch(textwin,locy,locx,' ');
            }else{
                mvwaddch(textwin,locy,locx,condicion);
                palabras=+condicion;
                locx++;
            }
        }while (condicion!=10);
        wattroff(textwin,A_REVERSE);
        mvwaddstr(textwin,18,2,"                                             ");
        locy=auxy;
        locx=auxx;
        wmove(textwin,locy,locx);
        if(condicion==10){
            std::string palabra;
            const char * c = palabra.c_str();
            scanw(c);
            //mvwinchstr(textwin,5,2,c);
            //mvwaddstr(textwin,locy,locy,"si funciona");
            //reemplazar(cadena,"nueva");
        }
        wrefresh(textwin);
    }else{
        if(locx==maxx-2){
            locy++;
            locx=2;
            this->boublelist.insertarFinal(choice,false);
        }else
            locx++;
        mvwaddch(textwin,locy,locx,choice);
        this->boublelist.insertarFinal(choice,false);
        this->unDo->push("NULL","NULL",false,choice,(locy-1)*72);
    }

    return choice;
}

void inputwin::typing(char caracter){
    inputwin::boublelist.insertarFinal(caracter,false);
    mvwaddch(textwin,locy,locx,caracter);
}

void inputwin::reemplazar(std::string palabra,std::string nueva){

}
