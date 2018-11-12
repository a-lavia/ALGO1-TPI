#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

TEST(enCrecimientoTEST, toroideDiagonalSeHaceTodoTrue){
    toroide t1 = { 
                  {true, false, false}, 
                  {false, true, false}, 
                  {false, false, true}};
    bool res = enCrecimiento(t1);
    EXPECT_FALSE(res);
}

TEST(enCrecimientoTEST, todoFalsoNoCrece){
    toroide t1 = {
            {false, false, false},
            {false, false, false},
            {false, false, false}};
    bool res = enCrecimiento(t1);
    EXPECT_FALSE(res);
}

TEST(enCrecimientoTEST, toroidePeriodicoNoCrece){
    toroide t1 = {
            {false, false, false, false},
            {true,  true,  true,  false},
            {false, false, false, false},
            {false, false, false, false}};
    bool res = enCrecimiento(t1);
    EXPECT_FALSE(res);
}

TEST(enCrecimientoTEST, toroideLSeHaceBloque){
    toroide t1 = {
            {false, false, false, false},
            {false, true,  true,  false},
            {false, false, true,  false},
            {false, false, false, false}};
    bool res = enCrecimiento(t1);
    EXPECT_FALSE(res);
}

TEST(enCrecimientoTEST, toroideExtremosEsBloque){
    toroide t1 = {
            {true,  false, false, true},
            {false, false, false, false},
            {false, false, false, false},
            {true,  false, false, true}};
    bool res = enCrecimiento(t1);
    EXPECT_FALSE(res);
}

TEST(enCrecimientoTEST, toroideBloqueConUnoMasCrece){
    toroide t1 = {
            {false, false, true, false},
            {false, true,  true,  false},
            {false, true,  true,  false},
            {false, false, false, false}};
    bool res = enCrecimiento(t1);
    EXPECT_TRUE(res);
}

TEST(enCrecimientoTEST, toroideLineaDeCuatroCrece){
    toroide t1 = {
            {false, false, false, false},
            {true,  true,  true,  true},
            {false, false, false, false},
            {false, false, false, false}};
    bool res = enCrecimiento(t1);
    EXPECT_TRUE(res);
}
