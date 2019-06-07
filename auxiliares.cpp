#include <algorithm>
#include "auxiliares.h"

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}

gps obtenerEsquinaSuperior(celda c) {
    return get<1>(c);
}

gps obtenerEsquinaInferior(celda c) {
    return get<0>(c);
}


nombre obtenerNombre(celda c) {
    return get<2>(c);
}

double distMts(gps posicion1, gps posicion2){
    return distEnKM(posicion1, posicion2) * 1000;
}

double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}

gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

viaje quickSort(viaje v){
    if(v.size() > 1) {
        viaje min; viaje eq; viaje max;
        int pi = div(v.size(), 2).quot;
        int i = 0;
        while (i < v.size()) {
            if (obtenerTiempo(v[i]) < obtenerTiempo(v[pi])) {
                min.push_back(v[i]);
            } else if (obtenerTiempo(v[i]) > obtenerTiempo(v[pi])) {
                max.push_back(v[i]);
            } else {
                eq.push_back(v[i]);
            }
            i++;
        }
        return concatViaje(concatViaje(quickSort(min), eq), quickSort(max));
    }
    return v;
}

viaje concatViaje(viaje a, viaje b){
    viaje ab = a;
    for (int i = 0; i < b.size(); ++i) {
        ab.push_back(b[i]);
    }
    return ab;
}

double calcVel(tuple<tiempo,gps> a, tuple<tiempo,gps> b){
    return 	(distEnKM(obtenerPosicion(a),obtenerPosicion(b)) * 3600)/(obtenerTiempo(b)-obtenerTiempo(a));
}

bool cubierto(viaje v, distancia u, gps g){
    int i = 0;
    while(i < v.size() && distMts(obtenerPosicion(v[i]),g) >= u){
        i++;
    }
    return i < v.size();
}

celda makeCelda(gps esq1,gps esq2,int n,int i, int j){
    double rango = (obtenerLatitud(esq2) - obtenerLatitud(esq1)) / n;
    gps e1 = make_tuple( obtenerLatitud(esq1) + (rango * i) , obtenerLongitud(esq1) + (rango * j));
    gps e2 = make_tuple( obtenerLatitud(esq1) + (rango * (i+1)) , obtenerLongitud(esq1) + (rango * (j+1)));
    nombre name = make_tuple(i+1,j+1);
    return make_tuple(e1,e2,name);
}

bool esCeldaDeCoordenada(gps t, celda celda){
    bool latEnCelda = obtenerLatitud(obtenerEsquinaInferior(celda)) <= obtenerLatitud(t) && obtenerLatitud(t) < obtenerLatitud(obtenerEsquinaSuperior(celda));
    bool longEnCelda = obtenerLongitud(obtenerEsquinaInferior(celda)) <= obtenerLongitud(t) && obtenerLongitud(t) < obtenerLongitud(obtenerEsquinaSuperior(celda));
    return latEnCelda && longEnCelda;
}

int diferenciaEntreCeldas(nombre n1, nombre n2){
    int res = abs(get<0>(n1)-get<0>(n2)) + abs(get<1>(n1)-get<1>(n2)) - 1;
    return res;
}

distancia calculoDistHueco(tuple<tiempo,gps> pos1, tuple<tiempo,gps> pos2, tuple<tiempo,gps> hueco){
    tiempo t = obtenerTiempo(hueco) - obtenerTiempo(pos1);
    t /= (obtenerTiempo(pos2) - obtenerTiempo(pos1));
    distancia res = distMts(obtenerPosicion(pos2),obtenerPosicion(pos1));
    return res * t;
}

