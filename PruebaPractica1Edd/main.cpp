#include <iostream>
#include "listadoble.h"
#include "Pila.h"
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

int main()
{
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
    std::string indices;
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
file.close();
    return 0;
}


