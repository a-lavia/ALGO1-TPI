#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

TEST(fusionarTEST, sinInterseccion){
    toroide t1 = { 
                  {true, false, false},
                  {false, true, false},
                  {false, false, true}}; 
    toroide t2 = { 
                  {false, true, true},
                  {true, false, true},
                  {true, true, false}}; 
    toroide res = fusionar(t1, t2);
    EXPECT_EQ(res.size(), 3);
    EXPECT_EQ(res[0].size(), 3);
    EXPECT_EQ(res[1].size(), 3);
    EXPECT_EQ(res[2].size(), 3);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            EXPECT_FALSE(res[i][j]);
        }
    }
}

TEST(fusionarTEST, interseccionSoloDiagonal){
    toroide t1 = { 
                  {true, false, false},
                  {false, true, false},
                  {false, false, true}}; 
    toroide t2 = { 
                  {true, true, true},
                  {true, true, true},
                  {true, true, true}}; 
    toroide res = fusionar(t1, t2);
    EXPECT_EQ(res.size(), 3);
    EXPECT_EQ(res[0].size(), 3);
    EXPECT_EQ(res[1].size(), 3);
    EXPECT_EQ(res[2].size(), 3);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            if (i != j) EXPECT_FALSE(res[i][j]);
            else EXPECT_TRUE(res[i][j]);
        }
    }
}
