#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

void escribirGrilla(grilla g, string nombreArchivo){

}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {

}

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    float max =0;
    float min =0;

    for (int i = 0; i < v.size(); ++i) {
        float time = get<0>(v[i]);
        if(time > max){
            max = time;
        } else if(time < min){
            min = time;
        }
    }
    return max - min;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {

}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int res = 0;
    for (int i = 0; i < f.size(); ++i) {
        if (estaEnViaje(f[i],t0,tf)) res++;
    }
    return res;
}

bool estaEnViaje(viaje v, tiempo t0,tiempo tf){
    int i = 0;
    while (i < v.size() && (get<0>(v[i]) < t0 || get<0>(v[i]) > tf)){
        i++;
    }
    return i < v.size();
}
/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {

}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {

}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {

}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {

}


