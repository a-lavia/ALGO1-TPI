#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

TEST(soloBloquesTEST, toroideVacioEsBloque){
    toroide t = { 
                  {false, false, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_TRUE(res);
}

TEST(soloBloquesTEST, toroideConUnaViva){
    toroide t = { 
                  {false, false, false, false, false},
                  {false, true, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_FALSE(res);
}

TEST(soloBloquesTEST, toroidesChico){
    toroide t1 = { 
                  {true, true},
                  {true, true}};

    toroide t2 = { 
                  {true, true, false},
                  {true, true, false},
                  {false, false, false}};
    toroide t3 = { 
                  {true, true, false},
                  {true, false, false},
                  {false, false, false}};
    bool res = soloBloques(t1);
    EXPECT_FALSE(res);
    res = soloBloques(t2);
    EXPECT_TRUE(res);
    res = soloBloques(t3);
    EXPECT_FALSE(res);
}

TEST(soloBloquesTEST, toroideUnBloque){
    toroide t = { 
                  {true, true, false, false, false},
                  {true, true, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false},
                  {false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_TRUE(res);
}

TEST(soloBloquesTEST, toroideDosBloques){
    toroide t = { 
                  {true, true, false, false, false, false},
                  {true, true, false, false, false, false},
                  {false, false, false, true, true, false},
                  {false, false, false, true, true, false},
                  {false, false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_TRUE(res);
}

TEST(soloBloquesTEST, toroideCasiBloque){
    toroide t = { 
                  {true, true, false, false, false, false},
                  {true, true, false, false, false, false},
                  {false, false, false, true, false, false},
                  {false, false, false, false, false, false},
                  {false, false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_FALSE(res);
}

TEST(soloBloquesTEST, toroideNoRespetaEspacioDeBloque){
    toroide t = { 
                  {true, true, false, false, false, false},
                  {true, true, false, false, false, false},
                  {false, false, true, true, false, false},
                  {false, false, true, true, false, false},
                  {false, false, false, false, false, false}};

    bool res = soloBloques(t);
    EXPECT_FALSE(res);
}

TEST(soloBloquesTEST, toroideBloqueEnExtremos){
    toroide t = { 
                  {true, false, false, false, false, true},
                  {false, false, false, false, false, false},
                  {false, false, false, false, false, false},
                  {false, false, false, false, false, false},
                  {true, false, false, false, false, true}};

    bool res = soloBloques(t);
    EXPECT_TRUE(res);
}

TEST(soloBloquesTEST, toroideVariosBloqueEnExtremos){
    toroide t = { 
                  {true, false, true, true, false, true},
                  {false, false, false, false, false, false},
                  {true, false, false, false, false, true},
                  {true, false, false, false, false, true},
                  {false, false, false, false, false, false},
                  {true, false, true, true, false, true}};

    bool res = soloBloques(t);
    EXPECT_TRUE(res);
}

TEST(soloBloquesTEST, toroideTodoVivo){
    toroide t = { 
                  {true, true, true, true, true, true},
                  {true, true, true, true, true, true},
                  {true, true, true, true, true, true},
                  {true, true, true, true, true, true},
                  {true, true, true, true, true, true}};

    bool res = soloBloques(t);
    EXPECT_FALSE(res);
}
