#include "../solucion.h"
#include "gtest/gtest.h"

using namespace std;

TEST(evolucionDePosicionTEST, toroideDiagonalTresPorTres){
    toroide t = { {true, false, false}, {false, true, false}, {false, false, true} };
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(1,1)));
}

TEST(evolucionDePosicionTEST, unaFilaTrueEnElMedio){
    toroide t = { {false, true, false}};
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(0,1)));
}
TEST(evolucionDePosicionTEST, unaColumnaTrueEnElMedio){
    toroide t = { {false},
                  {true},
                  {false}};
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(1, 0)));
}

TEST(evolucionDePosicionTEST, VivoTresVecinosVivos){
    toroide t = { {true, false, true}, {false, true, false}, {false, false, true} };
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(1,1)));
}
TEST(evolucionDePosicionTEST, VivoCuatroVecinosVivos){
    toroide t = { {true, false, true}, {true, true, false}, {false, false, true} };
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(1,1)));
}
TEST(evolucionDePosicionTEST, VivoCincoVecinosVivos){
    toroide t = { {true, false, true}, {true, true, false}, {true, false, true} };
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(1,1)));
}

TEST(evolucionDePosicionTEST, VivoVecinosAbajoALaDerecha){
    toroide t = { {true, false, false}, {true, true, false}, {false, false, false} };
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(0,0)));
}
TEST(evolucionDePosicionTEST, VivoVecinosDerechaYAbajo){
    toroide t = { {true, true, false}, {false, true, false}, {false, false, false} };
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(0,0)));
}
TEST(evolucionDePosicionTEST, DosFilas){
    toroide t = { {true, false, false}, {false, true, false}};
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(0,0)));
}
TEST(evolucionDePosicionTEST, TodoMuerto){
    toroide t = { {false, false, false}, {false, false, false}};
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(0,0)));
}
TEST(evolucionDePosicionTEST, Revive){
    toroide t = { {false, true, false}, {false, true, false}, {false, true, false}};
    EXPECT_TRUE(evolucionDePosicion(t, make_tuple(1,0)));
}
TEST(evolucionDePosicionTEST, NoRevivePorCuatroVecinosVivos){
    toroide t = { {false, true, true}, {false, true, false}, {false, true, false}};
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(1,0)));
}
TEST(evolucionDePosicionTEST, NoRevivePorCincoVecinosVivos){
    toroide t = { {false, true, true}, {false, true, false}, {false, true, true}};
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(1,0)));
}
TEST(evolucionDePosicionTEST, NoRevivePorDosVecinosVivos){
    toroide t = { {false, true, false}, {false, false, false}, {false, true, false}};
    EXPECT_FALSE(evolucionDePosicion(t, make_tuple(1,0)));
}
