#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

void escribirGrilla(grilla g, string nombreArchivo){
	ofstream f;
	f.open(nombreArchivo);
	if(!f.fail()){
		int i = 0;
		while(i < g.size()) {

			f << obtenerLatitud(get<0>(g[i]));
			f << obtenerLongitud(get<0>(g[i]));
			f << obtenerLatitud(get<1>(g[i]));
			f << obtenerLongitud(get<1>(g[i]));
			f << get<0>(get<2>(g[i]));
			f << get<1>(get<2>(g[i]));
			f << endl;
			i++;

		}
	}
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){
	ofstream f;
	f.open(nombreArchivo);
	if(!f.fail()){
		int i = 0;
		while (i < recorridos.size()){
			int j = 0;
			while(j < recorridos[i].size()){
				f << i;
				f << obtenerLatitud(recorridos[i][j]);
				f << obtenerLongitud(recorridos[i][j]);
				j++;
			}
			
			i++;
		}
	}
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
double calcVel(tuple<tiempo,gps> a, tuple<tiempo,gps> b){
	return 	(distEnKM(obtenerPosicion(a),obtenerPosicion(b))*3600)/(obtenerTiempo(b)-obtenerTiempo(a));
}

bool excesoDeVelocidad(viaje v) {
    v = quickSort(v);
    int i = 0;
    while(i < v.size()-1 && calcVel(v[i],v[i+1]) <= 80){
        i++;
    }
    return i < v.size()-1;
}

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo max =0;
    tiempo min =0;

    for (int i = 0; i < v.size(); ++i) {
        tiempo time = obtenerTiempo(v[i]);
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
    distancia dist = 0;
    for(int i = 0; i < v.size()-1 ; i++){
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
    while (i < v.size() && (obtenerTiempo(v[i]) < t0 || obtenerTiempo(v[i]) > tf)){
        i++;
    }
    return i < v.size();
}
/************************************ EJERCICIO recorridoCubierto *******************************/
bool cubierto(viaje v, distancia u, gps g){
    int i = 0;
    while(i<v.size() && distMts(obtenerPosicion(v[i]),g) >= u){
        i++;
    }
    return i < v.size();
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
    grilla g;
    double rango = (obtenerLatitud(esq2) - obtenerLatitud(esq1)) / n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            gps e1 = make_tuple( obtenerLatitud(esq1) + (rango * i) , obtenerLongitud(esq1) + (rango * j));
            gps e2 = make_tuple( obtenerLatitud(esq1) + (rango * (i+1)) , obtenerLongitud(esq1) + (rango * (j+1)));
            nombre n = make_tuple(i+1,j+1);
            g.push_back(make_tuple(e1,e2,n));
        }
    }
    return g;
}

/***************************************** EJERCICIO aPalabra **********************************/
bool esCeldaDeCoordenada(gps t, celda celda){
    bool latEnCelda = get<0>(get<1>(celda))<=get<0>(t) && get<0>(t) < get<0>(get<0>(celda));
    bool longEnCelda = get<1>(get<1>(celda))<=get<1>(t) && get<1>(t) < get<1>(get<0>(celda));
    return latEnCelda && longEnCelda;
}

vector<nombre> aPalabra(recorrido t, grilla g) {
    vector<nombre> res;
    int i = 0;
    while(i<t.size()) {
        int j = 0;
        while (j < g.size() && !esCeldaDeCoordenada(t[i], g[j])) {
            j++;
        }
        res.push_back(get<2>(g[j]));
        i++;
    }
    return res;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int res = 0;
    v = quickSort(v);
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
            if(esCeldaDeCoordenada(get<1>(v[i]),g[i])) res++;
        }
    }
    return res;
}


