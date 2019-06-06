#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"


double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
nombre obtenerNombre(celda c);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
double distMts(gps posicion1, gps posicion2);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
viaje quickSort(viaje v);
viaje concatViaje(viaje a, viaje b);
distancia calculoDistHueco(tuple<tiempo,gps> pos1, tuple<tiempo,gps> pos2, tuple<tiempo,gps> hueco);
bool esCeldaDeCoordenada(gps t, celda celda);
int diferenciaEntreCeldas(nombre n1, nombre n2);
bool cubierto(viaje v, distancia u, gps g);
double calcVel(tuple<tiempo,gps> a, tuple<tiempo,gps> b);
celda makeCelda(gps esq1,gps esq2,int n,int i, int j);

#endif //TRANSPORTEURBANO_AUXILIARES_H
