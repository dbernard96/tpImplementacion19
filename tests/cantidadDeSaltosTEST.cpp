#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, noHaySaltos){
    grilla g = construirGrilla(make_tuple(0,0),make_tuple(1,1),2,2);

    viaje v = {make_tuple(0,make_tuple(0,0)),make_tuple(1,make_tuple(0.99,0)),
               make_tuple(2,make_tuple(0.99,0.99))};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosTEST, haySaltos){
    grilla g = construirGrilla(make_tuple(0,0),make_tuple(3,3),3,3);

    viaje v = {make_tuple(0,make_tuple(0,0)),make_tuple(1,make_tuple(2,0)),
               make_tuple(2,make_tuple(2,2)),make_tuple(3,make_tuple(0,0))};

    EXPECT_EQ(cantidadDeSaltos(g,v),3);
}