#include "solucion.h"

using namespace std;

int filas(toroide& t) {
    return t.size();
}

int columnas(toroide& t) {
    return filas(t) > 0 ? t[0].size() : 0;
}

int mod(int x, int m) {
    int r = x%m;
    return r<0 ? r+m : r;
}

bool viva(toroide& t, int x, int y) {
    return t[mod(x, filas(t))][mod(y, columnas(t))];
}

int cantidadDeVivas(toroide& t) {
    int res = 0;
    for (int i = 0; i < filas(t); ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            if (viva(t, i, j)) {
                res++;
            }
        }
    }
    return res;
}

int superficieTotal(toroide& t) {
    return filas(t) * columnas(t);
}

int vecinosVivos(toroide& t, int x, int y) {
    int res = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ( (i != 0 || j != 0) && viva(t, x+i, y+j)) {
                res++;
            }
        }
    }
    return res;
}

bool debeVivir(toroide& t, posicion& p) {
    bool estaViva = viva(t, get<0>(p), get<1>(p));
    int vecinos = vecinosVivos(t, get<0>(p), get<1>(p));
    return (estaViva && vecinos == 2) || vecinos == 3;
}
/********************************** EJERCICIO esValido **********************************/
bool esValido(toroide t){
    bool res = true;
    for (int i = 0; i < filas(t) ; ++i) {
        if(t[i].size() == columnas(t)) {
            res = true;
        } else {
            res = false;
            break;
        }
    }
    return res;
}

/****************************** EJERCICIO posicionesVivas *******************************/
vector<posicion> posicionesVivas(toroide t){
    vector<posicion> res;
    for (int i = 0; i < filas(t) ; ++i) {
        for (int j = 0; j < columnas(t) ; ++j) {
            if(viva(t, i, j)){
                res.push_back(make_tuple(i,j));
            }
        }
    }
    return res;
}

/***************************** EJERCICIO densidadPoblacion ******************************/
float densidadPoblacion(toroide t){
    return (float)cantidadDeVivas(t)/superficieTotal(t);
}

/**************************** EJERCICIO evolucionDePosicion *****************************/
bool evolucionDePosicion(toroide t, posicion p){
    return debeVivir(t, p);
}

/****************************** EJERCICIO evolucionToroide ******************************/
void evolucionToroide(toroide& t){
    toroide tOriginal = t;
    for (int i = 0; i < filas(t) ; ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            t[i][j] = evolucionDePosicion(tOriginal, make_tuple(i, j));
        }
    }
}

/***************************** EJERCICIO evolucionMultiple ******************************/
toroide evolucionMultiple(toroide t, int k){
    toroide tCopia = t;
    for (int i = 0; i < k; ++i) evolucionToroide(tCopia);
    return tCopia;
}

/******************************** EJERCICIO esPeriodico *********************************/
bool esPeriodico(toroide t, int& p){
    toroide tCopia = t;
    toroide tMuerto = t;
    for (int i = 0; i < filas(t) ; ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            tMuerto[i][j] = false;
        }
    }
    int periodo = 0;
    if (tCopia == tMuerto) {
        p = 1;
        return true;
    }
    do {
        periodo++;
        evolucionToroide(tCopia);
        if (tCopia == tMuerto) {
            return false;
        }
    } while (tCopia != t);
    p = periodo;
    return true;
}

/******************************* EJERCICIO primosLejanos ********************************/
bool primosLejanos(toroide t1, toroide t2) {
    return false;
}

/****************************** EJERCICIO seleccionNatural ******************************/
int seleccionNatural(vector<toroide> ts){
    int indice;
    return indice;
}

/********************************** EJERCICIO fusionar **********************************/
toroide fusionar(toroide t1, toroide t2){
    toroide t = {
            {true, false, false},
            {false, true, false},
            {false, false, true}};
    return t;
}

/****************************** EJERCICIO vistaTrasladada *******************************/
bool vistaTrasladada(toroide t1, toroide t2){
    bool res = false;
    return res;
}

/******************************* EJERCICIO enCrecimiento ********************************/
bool enCrecimiento(toroide t){
    bool res;
    return res;
}

/******************************* EJERCICIO soloBloques (OPCIONAL) ***********************/
bool soloBloques(toroide t){
    bool res;
    return res;
}
