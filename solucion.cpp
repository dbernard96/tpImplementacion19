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

			f << obtenerLatitud(get<0>(g[i])) << '\t';
			f << obtenerLongitud(get<0>(g[i])) << '\t';
			f << obtenerLatitud(get<1>(g[i])) << '\t';
			f << obtenerLongitud(get<1>(g[i])) << '\t';
			f << "(" << get<0>(get<2>(g[i]));
			f << "," << get<1>(get<2>(g[i])) << ")" << endl;
			i++;

		}
	}
	f.close();
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){
	ofstream f;
	f.open(nombreArchivo);
	if(!f.fail()){
		int i = 0;int j = 0;
		while (i < recorridos.size()){
			f << i << '\t';
			f << obtenerLatitud(recorridos[i][j]) << '\t';
			f << obtenerLongitud(recorridos[i][j]) << endl;

			if (j < recorridos[i].size()-1){
			    j++;
			}else{
			    j = 0;
			    i++;
			}
		}
	}
	f.close();
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
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
    tiempo max = obtenerTiempo(v[0]);
    tiempo min = obtenerTiempo(v[0]);
    for (int i = 1; i < v.size(); ++i) {
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
distancia distanciaTotal(viaje v) {
    v = quickSort(v);
    distancia dist = 0;
    for(int i = 0; i < v.size()-1 ; i++){
        dist = dist + distEnKM(obtenerPosicion(v[i]),obtenerPosicion(v[i+1]));
    }
    return dist;
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
    grilla g(n*m,make_tuple(make_tuple(0,0),make_tuple(0,0),make_tuple(0,0)));
    int i = 0;
    int j = 0;
    while(i < n){
        g[m * i + j] = (makeCelda(esq1,esq2,n,i,j));
        if(j < m - 1){
            j++;
        }else{
            i++;
            j=0;
        }
    }

    return g;
}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {
    vector<nombre> res(t.size(),make_tuple(0,0));
    int i = 0;
    while(i < t.size()) {
        int j = 0;
        while (j < g.size() && !esCeldaDeCoordenada(t[i], g[j])) {
            j++;
        }
        res[i] = obtenerNombre(g[j]);
        i++;
    }
    return res;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int res = 0;
    v = quickSort(v);
    vector<nombre> nombres(v.size(), make_tuple(0,0));
    for (int i = 0; i < v.size(); ++i) {
        int j = 0;
        while(!esCeldaDeCoordenada(obtenerPosicion(v[i]),g[j])){
            j++;
        }
        nombres[i] = obtenerNombre(g[j]);
    }

    for (int k = 0; k < nombres.size()-1; ++k) {
        if(diferenciaEntreCeldas(nombres[k],nombres[k+1]) >= 1){
            res++;
        }
    }

    return res;
}
/**************************************/
void completarHuecos(viaje& v, vector<int> faltantes){
    viaje vOrd = quickSort(v);
    gps hueco = make_tuple(-1000,-1000);
    for (int i = 0; i < faltantes.size(); ++i) {
        int min = faltantes[i];
        int max = faltantes[i];
        while(obtenerPosicion(vOrd[min])==hueco || obtenerPosicion(vOrd[max])==hueco){
            if(obtenerPosicion(vOrd[min])==hueco) min--;
            if(obtenerPosicion(vOrd[max])==hueco) max++;
        }
        distancia d = calculoDistHueco(vOrd[min],vOrd[max],vOrd[faltantes[i]]);
        v[faltantes[i]] = make_tuple(obtenerTiempo(v[faltantes[i]]),desviarPunto(obtenerPosicion(vOrd[min]), d,0));
    }
}
