#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

TEST(evolucionMultipleTEST, toroideDiagonalTresPorTresUnPaso){
    toroide t = { {true, false, false}, {false, true, false}, {false, false, true} };
    //1*0 0 1*0
    //0 1 0 0 1
    //0 0 1 0 0
    //1 0 0 1 0
    //0*1 0 0*1
    toroide evo_t = { {true, true, true}, {true, true, true}, {true, true, true} };
    //  1 1 1
    //  1 1 1
    //  1 1 1
    toroide res = evolucionMultiple(t, 1);
    EXPECT_EQ(res, evo_t);
}

TEST(evolucionMultipleTEST, toroideDiagonalTresPorTresDosPasos){
    toroide t = { {true, false, false}, {false, true, false}, {false, false, true} };
    // Ver toroideDiagonalTresPorTresUnPaso
    toroide evo_t = { {false, false, false}, {false, false, false}, {false, false, false} };
    toroide res = evolucionMultiple(t, 2);
    EXPECT_EQ(res, evo_t);
}
TEST(evolucionMultipleTEST, toroideTodoFalso20Pasos){
    toroide t = { {false, false, false}, {false, false, false}, {false, false, false} };
    toroide evo_t = { {false, false, false}, {false, false, false}, {false, false, false} };
    toroide res = evolucionMultiple(t, 20);
    EXPECT_EQ(res, evo_t);
}
TEST(evolucionMultipleTEST, toroideUnaFilaTrueEnCentro){
    toroide t = { {false, true, false}};
    //0*0 1 0*0
    //0 0 1 0 0
    //0*0 1 0*0
    toroide evo_t = { {true, true, true}};
    toroide res = evolucionMultiple(t, 1);
    EXPECT_EQ(res, evo_t);
}
TEST(evolucionMultipleTEST, toroideUnaColumnaTrueEnCentro){
    toroide t = { {false}, {true}, {false}};
    // Ver toroideUnaFilaTrueEnCentro
    toroide evo_t = { {true}, {true}, {true}};
    toroide res = evolucionMultiple(t, 1);
    EXPECT_EQ(res, evo_t);
}
TEST(evolucionMultipleTEST, toroideUnaFilaFTTF){
    toroide t = { {false, true, true, false}};
    //0*0 1 1 0*0
    //0 0 1 1 0 0
    //0*0 1 1 0*0
    toroide evo_t = { {true, false, false, true}};
    toroide res = evolucionMultiple(t, 1);
    EXPECT_EQ(res, evo_t);
}
TEST(evolucionMultipleTEST, toroide5EvolucionesVsEvolucion5){
    toroide t = {
        {false, false, false, false, false},
        {false, true, true, false, true},
        {false, false, true, false, true},
        {false, true, true, false, true},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, true, false, false, true}
    };
    //0*0 1 1 0*0
    //0 0 1 1 0 0
    //0*0 1 1 0*0
    toroide evo_1 = evolucionMultiple(t, 1);
    toroide evo_2 = evolucionMultiple(evo_1, 1);
    toroide evo_3 = evolucionMultiple(evo_2, 1);
    toroide evo_4 = evolucionMultiple(evo_3, 1);
    toroide evo_5 = evolucionMultiple(evo_4, 1);
    toroide res = evolucionMultiple(t, 5);
    EXPECT_EQ(res, evo_5);
}
