#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(flotaTEST, viajeEnteroEnRango){
    tuple<tiempo ,gps> t1 = make_tuple(5,make_tuple(0,0));
    tuple<tiempo ,gps> t2 = make_tuple(6,make_tuple(0,0));
    tuple<tiempo ,gps> t3 = make_tuple(7,make_tuple(0,0));
    viaje v = {t1,t2,t3};
    vector<viaje> f = {v};
    EXPECT_EQ(flota(f,4,8),1);
}

TEST(flotaTEST, noHayViajes){
    vector<viaje> f = {};
    EXPECT_EQ(flota(f,5,6),0);
}

TEST(flotaTEST, viajeMenorT0){
    tuple<tiempo ,gps> t1 = make_tuple(5,make_tuple(0,0));
    tuple<tiempo ,gps> t2 = make_tuple(6,make_tuple(0,0));
    tuple<tiempo ,gps> t3 = make_tuple(7,make_tuple(0,0));
    viaje v = {t1,t2,t3};
    vector<viaje> f = {v};
    EXPECT_EQ(flota(f,6,8),1);
}

TEST(flotaTEST, viajeMayorTf){
    tuple<tiempo ,gps> t1 = make_tuple(5,make_tuple(0,0));
    tuple<tiempo ,gps> t2 = make_tuple(6,make_tuple(0,0));
    tuple<tiempo ,gps> t3 = make_tuple(7,make_tuple(0,0));
    viaje v = {t1,t2,t3};
    vector<viaje> f = {v};
    EXPECT_EQ(flota(f,4,6),1);
}

TEST(flotaTEST, viajeSobresaleAmbos){
    tuple<tiempo ,gps> t1 = make_tuple(4,make_tuple(0,0));
    tuple<tiempo ,gps> t2 = make_tuple(6,make_tuple(0,0));
    tuple<tiempo ,gps> t3 = make_tuple(8,make_tuple(0,0));
    viaje v = {t1,t2,t3};
    vector<viaje> f = {v};
    EXPECT_EQ(flota(f,5,7),1);
}

TEST(flotaTEST, noHayViajesEnFlota){
    tuple<tiempo ,gps> t1 = make_tuple(5,make_tuple(0,0));
    tuple<tiempo ,gps> t2 = make_tuple(6,make_tuple(0,0));
    tuple<tiempo ,gps> t3 = make_tuple(7,make_tuple(0,0));
    viaje v = {t1,t2,t3};
    vector<viaje> f = {v};
    EXPECT_EQ(flota(f,10,11),0);
}