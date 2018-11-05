#include "../solucion.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;
vector<posicion> ordenar(vector<posicion> &v) {
    sort(v.begin(), v.end());
    return v;
}

TEST(posicionesVivasTEST, toroideVacio){
    toroide t = { vector<bool> () };
    vector<posicion> vacio;
    vector<posicion> res = posicionesVivas(t);
    EXPECT_EQ(vacio, res);
}

TEST(posicionesVivasTEST, toroideTodoPosicionesMuertas){
    vector<bool> filaMuerta = { false, false, false, false };
    toroide t = { filaMuerta, filaMuerta, filaMuerta, filaMuerta, filaMuerta, filaMuerta, filaMuerta };
    vector<posicion> vacio;
    vector<posicion> res = posicionesVivas(t);
    EXPECT_EQ(vacio, res);
}

tuple<int,int> mt(int a, int b) {
    return make_tuple(a, b);
}
TEST(posicionesVivasTEST, toroideDiagonalVivas){
    toroide t = { 
	{true, false, false},
	{false, true, false},
	{false, false, true},
	{true, false, false},
	{false, true, false},
	{false, false, true}};
   
    vector<posicion> vivas = {mt(0,0), mt(1,1), mt(2,2), mt(3, 0), mt(4, 1), mt(5, 2)};
    vector<posicion> res = posicionesVivas(t);
    EXPECT_EQ(ordenar(vivas), ordenar(res));
}
TEST(posicionesVivasTEST, toroideTodoPosicionesVivas){
    vector<bool> filaViva = { true, true, true };
    toroide t = { 
	filaViva,
	filaViva,
	filaViva,
	filaViva};
   
    vector<posicion> vivas = {
	mt(0,0), mt(0, 1), mt(0, 2),
	mt(1,0), mt(1, 1), mt(1, 2),
	mt(2,0), mt(2, 1), mt(2, 2),
	mt(3,0), mt(3, 1), mt(3, 2)};
    vector<posicion> res = posicionesVivas(t);
    EXPECT_EQ(ordenar(vivas), ordenar(res));
}
TEST(posicionesVivasTEST, unaFila){
    toroide t = { 
	{true, false, true}};
   
    vector<posicion> vivas = {mt(0,0), mt(0,2)};
    vector<posicion> res = posicionesVivas(t);
    EXPECT_EQ(ordenar(vivas), ordenar(res));
}
