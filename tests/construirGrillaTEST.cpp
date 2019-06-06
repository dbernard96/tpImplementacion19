#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

//TEST(construirGrillaTEST,)

TEST(construirGrillaTEST, ){
    gps esq1 = make_tuple(-1,-1);
    gps esq2 = make_tuple(1,1);

    celda c0 = make_tuple(make_tuple(-1,-1),make_tuple(0,0),make_tuple(1,1));
    celda c1 = make_tuple(make_tuple(-1,0),make_tuple(0,1),make_tuple(1,2));
    celda c2 = make_tuple(make_tuple(0,-1),make_tuple(1,0),make_tuple(2,1));
    celda c3 = make_tuple(make_tuple(0,0),make_tuple(1,1),make_tuple(2,2));

    grilla g = {c0,c1,c2,c3};

    EXPECT_EQ(construirGrilla(esq1,esq2,2,2),g);
}