//#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <string>

using namespace std;
void pantallamenu();
void pantallatext();
int main()
{
    pantallamenu();
    return 0;
}

void pantallamenu(){
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
    printw("Escojiste> %s",opcions[highlited].c_str());
    if(opcions[highlited]=="1.Crear Archivo"){
        pantallatext();
    }
    getch();
    endwin();
    //std::cout << "Hello World funcionara esto?!" << endl;
}

void pantallatext(){
    initscr();
    WINDOW *textwin=newwin(22,76,1,1);
    box(textwin,0,0);
    wrefresh(textwin);
    getch();
    endwin();
    pantallamenu();
}
