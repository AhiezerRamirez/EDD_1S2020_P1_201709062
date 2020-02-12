#include "estructura.h"

Estructura::Estructura(){
}

void Estructura::abrirInput(){
    initscr();
    inputwin=newwin(22,76,1,1);
    box(inputwin,0,0);
    wrefresh(inputwin);
    mvwhline(inputwin,30,1,'-',139);
    mvwaddstr(inputwin,31,1,"^w(Buscar y Reemplazar  ^c(Reportes)    ^s(Guardar)");
    int c=wgetch(inputwin);
    getch();
    endwin();
}
