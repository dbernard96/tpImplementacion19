#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"
#include "tuple"

using namespace std;

TEST(excesoDeVelocidadTEST, excesoDeVelocidad){
    tuple<tiempo, gps> v1 = make_tuple(0,make_tuple(0,0));
    tuple<tiempo, gps> v2 = make_tuple(1,make_tuple(90,90));
    tuple<tiempo, gps> v3 = make_tuple(2, make_tuple(0,0));
    viaje v = {v1,v2,v3};
    EXPECT_EQ(excesoDeVelocidad(v),true);
}

TEST(excesoDeVelocidadTEST, noExcesoDeVelocidad){
    tuple<tiempo, gps> v1 = make_tuple(0,make_tuple(0,0));
    tuple<tiempo, gps> v2 = make_tuple(1,desviarPunto(get<1>(v1),15,0));
    tuple<tiempo, gps> v3 = make_tuple(2, make_tuple(0,0));
    viaje v = {v1,v2,v3};
    EXPECT_EQ(excesoDeVelocidad(v), false);
}