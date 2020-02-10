#include "inputwin.h"
#define ctl(w) ((w) & 0x1f)
#define ctl2(x) ((x) & 0x1f)
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>

inputwin::inputwin(WINDOW *win, int y, int x){
    textwin=win;
    this->locy=y;
    this->locx=x;
    getmaxyx(textwin,maxy,maxx);
}

int inputwin::getmv(){

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
        int auxx=locx;
        int auxy=locy;
        mvwprintw(textwin,29,2,"Buscar y remplazar  ");
        int auxlocx=locx=getcurx(textwin);
        int auxlocy=locy=getcury(textwin);
        int condicion=0;                        // es para parar el while
        wattron(textwin,A_REVERSE);
         do{
            condicion=wgetch(textwin);
            mvwaddch(textwin,locy,locx,condicion);
            locx++;
        }while (condicion!=10 || condicion==ctl2('x'));
        wattroff(textwin,A_REVERSE);
        mvwaddstr(textwin,auxlocy,auxlocx,"                                             ");
        locy=auxy;
        locx=auxx;
        wmove(textwin,locy,locx);
        if(condicion==10){
            std::string cadena,nueva;
            mvwinnstr(textwin, locy, 2, const_cast<char*>(cadena.c_str()), locx);
            reemplazar(cadena,"nueva");
        }
        wrefresh(textwin);
    }else{
        if(locx==maxx-2){
            locy++;
            locx=2;
        }else
            locx++;
        mvwaddch(textwin,locy,locx,choice);
    }

    return choice;
}

void inputwin::typing(char caracter){
    inputwin::boublelist.insertarFinal(caracter,false);
    mvwaddch(textwin,locy,locx,caracter);
}

void inputwin::reemplazar(std::string palabra,std::string nueva){
    int tama=palabra.size();
    int fin=nueva.size();
    char p[nueva.size()];
    char auxp=p[0];
    std::string cadena=inputwin::boublelist.buscar(palabra);         //retorna una cadena con los n[umeros encontrados

    std::vector<std::string> result;
    size_t found;

    std::string linea = cadena;
    found = linea.find(",");
    result.push_back(linea.substr(0,found));
    result.push_back(linea.substr(found+1,linea.size()) );       // separa los n[umeros encontrados

    for (int i = 0; i < result.size(); i++){                    // For para ir borrando las palabras encontradas

        for (int var = std::stoi(result[i]); var < tama+1; ++var) {        // con los otros dos for de abajo
            inputwin::boublelist.borrarEn(var);
        }
        for (int var = std::stoi(result[i]); var < fin+1; ++var) {
            inputwin::boublelist.insertertarEn(tama,auxp,false);
        }
    }


}
