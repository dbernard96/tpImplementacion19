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
	bool res = true;
	while(i < v.size()-1){
	    if(calcVel(v[i],v[i+1]) >= 80){
	        return res;
	    }
		i++;
	}
	return !res;
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
double distanciaViaje(viaje v){
    double dist = 0;
    for(int i=0;i<v.size()-1;i++){
        dist = dist + distEnKM(obtenerPosicion(v[i]),obtenerPosicion(v[i+1]));
    }
    return dist;

}

distancia distanciaTotal(viaje v) {
    v = quickSort(v);
    return distanciaViaje(v);

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
bool cubierto(viaje v, distancia u, gps g){
    int i = 0;
    bool res = false;
    while(i<v.size()){
        if(distEnKM(obtenerPosicion(v[i]),g)<u){
            return !res;
        }
        i++;
    }
    return res;
}

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> res;
    int i = 0;
    while(i<r.size()){
        if(!cubierto(v,u,r[i])) {
            res.push_back(r[i]);
        }
        i++;
    }
    return res;
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


