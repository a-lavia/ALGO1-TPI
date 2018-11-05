#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

TEST(evolucionToroideTEST, toroideDiagonalTresPorTresUnPaso){
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
    evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}

TEST(evolucionToroideTEST, toroideDiagonalTresPorTresDosPasos){
    toroide t = { {true, false, false}, {false, true, false}, {false, false, true} };
    // Ver toroideDiagonalTresPorTresUnPaso
    toroide evo_t = { {false, false, false}, {false, false, false}, {false, false, false} };
    evolucionToroide(t);
    evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}
TEST(evolucionToroideTEST, toroideTodoFalso20Pasos){
    toroide t = { {false, false, false}, {false, false, false}, {false, false, false} };
    toroide evo_t = { {false, false, false}, {false, false, false}, {false, false, false} };
    for (int i = 0; i < 20; ++i)
        evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}
TEST(evolucionToroideTEST, toroideUnaFilaTrueEnCentro){
    toroide t = { {false, true, false}};
    //0*0 1 0*0
    //0 0 1 0 0
    //0*0 1 0*0
    toroide evo_t = { {true, true, true}};
    evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}
TEST(evolucionToroideTEST, toroideUnaColumnaTrueEnCentro){
    toroide t = { {false}, {true}, {false}};
    // Ver toroideUnaFilaTrueEnCentro
    toroide evo_t = { {true}, {true}, {true}};
    evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}
TEST(evolucionToroideTEST, toroideUnaFilaFTTF){
    toroide t = { {false, true, true, false}};
    //0*0 1 1 0*0
    //0 0 1 1 0 0
    //0*0 1 1 0*0
    toroide evo_t = { {true, false, false, true}};
    evolucionToroide(t);
    EXPECT_EQ(t, evo_t);
}
TEST(evolucionToroideTEST, toroide5EvolucionesVsEvolucion5){
    toroide t = {
        {false, false, false, false, false},
        {false, true, true, false, true},
        {false, false, true, false, true},
        {false, true, true, false, true},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, true, false, false, true}
    };
    toroide t2 = t;
    for (int i = 0; i < 5; ++i) evolucionToroide(t);
    toroide evo_5 = evolucionMultiple(t2, 5); 
    EXPECT_EQ(t, evo_5);
}
