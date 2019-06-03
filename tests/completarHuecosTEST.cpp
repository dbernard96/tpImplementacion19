#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(completarHuecosTEST, noHayHuecos){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(2,2)),make_tuple(2,make_tuple(3,2))};
    vector<int> faltantes = {};
    viaje v0 = v;
    completarHuecos(v,faltantes);
    EXPECT_EQ(v,v0);
}

TEST(completarHuecosTEST,unSoloHueco){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(2,make_tuple(3,2))};
    vector<int> faltantes = {1};
    completarHuecos(v,faltantes);

    EXPECT_EQ(distMts(get<1>(v[1]),get<1>(v[0])), calculoDistHueco(v[0],v[2],v[1]));
}

TEST(completarHuecosTEST, multiplesHuecosSeparados){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(2,make_tuple(3,2)),
            make_tuple(3,make_tuple(3,3)),make_tuple(4,make_tuple(-1000,-1000)),make_tuple(5,make_tuple(4,3))};
    vector<int> faltantes = {1,4};
    completarHuecos(v,faltantes);

    for (int i = 0; i < faltantes.size(); ++i) {
        distancia res = distMts(obtenerPosicion(v[faltantes[i]]),obtenerPosicion(v[faltantes[i]-1]));
        EXPECT_EQ(res,calculoDistHueco(v[faltantes[i]-1],v[faltantes[i]+1],v[faltantes[i]]));
    }
}

TEST(completarHuecosTEST,multiplesHuecosJuntos){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),
               make_tuple(4,make_tuple(-1000,-1000)),make_tuple(5,make_tuple(4,3))};
    vector<int> faltantes = {1,2};
    completarHuecos(v,faltantes);

    for (int i = 0; i < faltantes.size(); ++i) {
        distancia res = distMts(obtenerPosicion(v[faltantes[i]]),obtenerPosicion(v[0]));
        EXPECT_EQ(res,calculoDistHueco(v[0],v[v.size()-1],v[faltantes[i]]));
    }
}
