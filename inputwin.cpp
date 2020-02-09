#include "inputwin.h"
#define ctl(w) ((w) & 0x1f)

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
        }while (condicion!=10);
        wattroff(textwin,A_REVERSE);
        mvwaddstr(textwin,auxlocy,auxlocx,"                                             ");
        locy=auxy;
        locx=auxx;
        wmove(textwin,locy,locx);
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
    mvwaddch(textwin,locy,locx,caracter);
}
