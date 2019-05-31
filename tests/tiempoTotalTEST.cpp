#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(tiempoTotalTEST, viajeOrdenado){
    viaje v = {make_tuple(0,make_tuple(0,0)),make_tuple(1,make_tuple(0,0)),make_tuple(2,make_tuple(0,0))};
    EXPECT_EQ(tiempoTotal(v),2);
}

TEST(tiempoTotalTEST, viajeNoOrdenado){
    viaje v = {make_tuple(2,make_tuple(0,0)),make_tuple(0,make_tuple(0,0)),make_tuple(1,make_tuple(0,0))};
    EXPECT_EQ(tiempoTotal(v),2);
}