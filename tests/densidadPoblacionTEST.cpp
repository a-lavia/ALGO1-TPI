#include "../solucion.h"
#include "gtest/gtest.h"

using namespace std;

TEST(densidadPoblacionTEST, toroideUnaFilaTodoMuerto){
    toroide t = { {false}, {false} };
    EXPECT_NEAR(densidadPoblacion(t), 0.0, 0.01);
}
TEST(densidadPoblacionTEST, toroideUnaColumnaTodoMuerto){
    toroide t = { {false}, {false} };
    EXPECT_NEAR(densidadPoblacion(t), 0.0, 0.01);
}
TEST(densidadPoblacionTEST, toroideDiagonal){
    toroide t = { {true, false}, {false, true} };
    EXPECT_NEAR(densidadPoblacion(t), 0.5, 0.01);
}
TEST(densidadPoblacionTEST, DosDivididoTres){
    toroide t = { {true, false, true} };
    EXPECT_NEAR(densidadPoblacion(t), 0.666, 0.01);
}
TEST(densidadPoblacionTEST, TodoVivo){
    toroide t = { {true, true, true},
	{true, true, true},
	{true, true, true},
	{true, true, true}};
    EXPECT_NEAR(densidadPoblacion(t), 1.0, 0.01);
}
