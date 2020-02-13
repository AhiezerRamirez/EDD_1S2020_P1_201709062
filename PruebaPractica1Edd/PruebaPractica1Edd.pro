TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    listadoble.cpp \
    Pila.cpp \
    estructura.cpp \
    listasimplecircular.cpp \
    listasimpleordenada.cpp \
    listacircular.cpp \
    inputwin.cpp

HEADERS += \
    ../Practica1Edd20/listadoble.h \
    listadoble.h \
    Pila.h \
    estructura.h \
    listasimplecircular.h \
    listasimpleordenada.h \
    listacircular.h \
    /usr/include/ncursesw/ncurses.h \
    /usr/include/ncurses.h \
    inputwin.h

QMAKE_CXXFLAGS += -lncurses
LIBS += -L/usr/include -lncurses
