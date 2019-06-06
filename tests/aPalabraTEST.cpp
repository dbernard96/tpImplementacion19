#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(aPalabraTEST, trayectoVacio){
    recorrido r = {};
    grilla g = construirGrilla(make_tuple(0,0),make_tuple(1,1),2,2);
    EXPECT_EQ(aPalabra(r,g).size(),0);
}

TEST(aPalabraTEST, trayectoNoVacio){
    recorrido r = {make_tuple(-1,-1),make_tuple(-0.22,-0.22),make_tuple(0.22,0.22),
                   make_tuple(0.9,0.9)};

    grilla g = construirGrilla(make_tuple(-1,-1),make_tuple(1,1),3,3);

    vector<nombre> resC = {make_tuple(1,1),make_tuple(2,2),make_tuple(2,2),make_tuple(3,3)};
    vector<nombre> res = aPalabra(r,g);

    EXPECT_EQ(resC,res);
}
