#include "inputwin.h"

inputwin::inputwin(WINDOW *win, int y, int x){
    textwin=win;
    this->locy=y;
    this->locx=x;
    getmaxyx(textwin,maxy,maxx);
}

int inputwin::getmv(){
    if(locx==maxx-2){
        locy++;
        locx=2;
    }else
        locx++;
    int choice=wgetch(textwin);

    if(choice==127){
        if(locx==2){
            locx=maxx-2;
            locy--;
            mvwaddch(textwin,locy,locx,' ');
        }else if(locy==2 && locx==2){
            mvwaddch(textwin,locy,locx,' ');
        }else{
            locx-=2;
        }
    }
    mvwaddch(textwin,locy,locx,choice);
    return choice;
}

void inputwin::typing(char caracter){
    mvwaddch(textwin,locy,locx,caracter);
}
