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

TEST(completarHuecosTEST,unSoloHuecoOrd){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(2,make_tuple(3,2))};
    vector<int> faltantes = {1};
    completarHuecos(v,faltantes);

    EXPECT_EQ(distMts(get<1>(v[1]),get<1>(v[0])), calculoDistHueco(v[0],v[2],v[1]));
}

TEST(completarHuecosTEST, multiplesHuecosSeparadosOrd){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(2,make_tuple(3,2)),
            make_tuple(3,make_tuple(3,3)),make_tuple(4,make_tuple(-1000,-1000)),make_tuple(5,make_tuple(4,3))};
    vector<int> faltantes = {1,4};
    completarHuecos(v,faltantes);

    for (int i = 0; i < faltantes.size(); ++i) {
        distancia res = distMts(obtenerPosicion(v[faltantes[i]]),obtenerPosicion(v[faltantes[i]-1]));
        EXPECT_EQ(res,calculoDistHueco(v[faltantes[i]-1],v[faltantes[i]+1],v[faltantes[i]]));
    }
}

TEST(completarHuecosTEST,multiplesHuecosJuntosOrd){
    viaje v = {make_tuple(0,make_tuple(1,2)),make_tuple(1,make_tuple(-1000,-1000)),
               make_tuple(4,make_tuple(-1000,-1000)),make_tuple(5,make_tuple(4,3))};
    vector<int> faltantes = {1,2};
    completarHuecos(v,faltantes);

    for (int i = 0; i < faltantes.size(); ++i) {
        distancia res = distMts(obtenerPosicion(v[faltantes[i]]),obtenerPosicion(v[0]));
        EXPECT_EQ(res,calculoDistHueco(v[0],v[v.size()-1],v[faltantes[i]]));
    }
}

TEST(completarHuecosTEST,unSoloHuecoNoOrd){
    viaje v = {make_tuple(2,make_tuple(3,2)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(0,make_tuple(1,2))};
    vector<int> faltantes = {1};
    completarHuecos(v,faltantes);

    EXPECT_EQ(distMts(get<1>(v[1]),get<1>(v[2])), calculoDistHueco(v[2],v[0],v[1]));
}

TEST(completarHuecosTEST, multiplesHuecosSeparadosNoOrd){
    viaje v = {make_tuple(5,make_tuple(4,3)),make_tuple(1,make_tuple(-1000,-1000)),make_tuple(2,make_tuple(3,2)),
               make_tuple(0,make_tuple(1,2)),make_tuple(4,make_tuple(-1000,-1000)),make_tuple(3,make_tuple(3,3))};
    vector<int> faltantes = {1,4};

    completarHuecos(v,faltantes);

    distancia res = distMts(obtenerPosicion(v[faltantes[0]]),obtenerPosicion(v[3]));
    EXPECT_EQ(res,calculoDistHueco(v[3],v[2],v[faltantes[0]]));

    res = distMts(obtenerPosicion(v[faltantes[1]]),obtenerPosicion(v[5]));
    EXPECT_EQ(res,calculoDistHueco(v[5],v[0],v[faltantes[1]]));

}

TEST(completarHuecosTEST,multiplesHuecosJuntosNoOrd){
    viaje v = {make_tuple(5,make_tuple(4,3)),make_tuple(1,make_tuple(-1000,-1000)),
               make_tuple(4,make_tuple(-1000,-1000)),make_tuple(0,make_tuple(1,2))};
    vector<int> faltantes = {1,2};
    completarHuecos(v,faltantes);

    for (int i = 0; i < faltantes.size(); ++i) {
        distancia res = distMts(obtenerPosicion(v[faltantes[i]]),obtenerPosicion(v[v.size()-1]));
        EXPECT_EQ(res,calculoDistHueco(v[v.size()-1],v[0],v[faltantes[i]]));
    }
}