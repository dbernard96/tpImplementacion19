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
double calcVel(tuple<tiempo,gps> a, tuple<tiempo,gps> b){
	return 	distEnKM(obtenerPosicion(a),obtenerPosicion(b)) * (1/3600) * (1/(obtenerTiempo(b)-obtenerTiempo(a)));
}

bool excesoDeVelocidad(viaje v) {
	v = quickSort(v);
	int i = 0;
	while(i < v.size()-1 && calcVel(v[i],v[i+1]) <= 80){
		i++;
	}
    return i < v.size();
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
    grilla g;
    float rango = (get<0>(esq2) - get<0>(esq1))/n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            gps e1 = make_tuple(get<0>(esq1)+rango*i,get<1>(esq1)+rango*j);
            gps e2 = make_tuple(get<0>(esq1)+rango*(i+1),get<1>(esq1)+rango*(j+1));
            nombre n = make_tuple(i+1,j+1);
            g.push_back(make_tuple(e1,e2,n));
        }
    }
    return g;
}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {

}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {

}


