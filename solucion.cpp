#include "solucion.h"

using namespace std;

/********************************** Auxiliares **********************************/

int filas(toroide t) {
    return t.size();
}

int columnas(toroide t) {
    return filas(t) > 0 ? t[0].size() : 0;
}

int mod(int x, int m) {
    int r = x % m;
    return r < 0 ? r + m : r;
}

bool viva(toroide t, int x, int y) {
    return t[mod(x, filas(t))][mod(y, columnas(t))];
}

int cantidadDeVivas(toroide t) {
    int res = 0;
    for (int i = 0; i < filas(t); ++i)
        for (int j = 0; j < columnas(t); ++j)
            if (viva(t, i, j)) res++;
    return res;
}

int superficieTotal(toroide t) {
    return filas(t) * columnas(t);
}

int vecinosVivos(toroide t, int x, int y) {
    int res = 0;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if ((i != 0 || j != 0) && viva(t, x + i, y + j)) res++;
    return res;
}

bool debeVivir(toroide t, posicion p) {
    bool estaViva = viva(t, get<0>(p), get<1>(p));
    int vecinos = vecinosVivos(t, get<0>(p), get<1>(p));
    return (estaViva && vecinos == 2) || vecinos == 3;
}

bool elToroideMuere(toroide t) {
    while (true) {
        int p;
        if (cantidadDeVivas(t) == 0) {
            return true;
        } else if (esPeriodico(t, p)) {
            return false;
        }
        evolucionToroide(t);
    }
}

int muereEn(toroide t) {
    int contador = 0;
    while (cantidadDeVivas(t) != 0) {
        evolucionToroide(t);
        contador++;
    }
    return contador;
}

int calcularMinimaSuperficie(toroide t) {
    int min_x = filas(t);
    int min_y = columnas(t);
    int max_x = 0;
    int max_y = 0;

    for (int i = 0; i < filas(t); ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            min_x = viva(t, i, j) ? min(i, min_x) : min_x;
            min_y = viva(t, i, j) ? min(j, min_y) : min_y;
            max_x = viva(t, i, j) ? max(i, max_x) : max_x;
            max_y = viva(t, i, j) ? max(j, max_y) : max_y;
        }
    }
    return (max_x - min_x) * (max_y - min_y);
}

bool esSubBloque(toroide t, int x, int y, toroide subt) {
    bool res = true;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            res = res && (viva(t, x+i, y+j) == subt[i+1][j+1]);
    return res;
}

bool esBloque(toroide t, int x, int y) {
    toroide t1 = { 
                  {false, false, false},
                  {false, true, true},
                  {false, true, true}};
    toroide t2 = { 
                  {false, true, true},
                  {false, true, true},
                  {false, false, false}};
    toroide t3 = { 
                  {true, true, false},
                  {true, true, false},
                  {false, false, false}};
    toroide t4 = { 
                  {false, false, false},
                  {true, true, false},
                  {true, true, false}};
    return esSubBloque(t, x, y, t1) || esSubBloque(t, x, y, t2) || esSubBloque(t, x, y, t3) || esSubBloque(t, x, y, t4);
}

/********************************** EJERCICIO esValido **********************************/
bool esValido(toroide t) {
    if (filas(t) * columnas(t) == 0) return false;
    for (int i = 0; i < filas(t); ++i)
        if (t[i].size() != columnas(t)) return false;
    return true;
}

/****************************** EJERCICIO posicionesVivas *******************************/
vector<posicion> posicionesVivas(toroide t) {
    vector<posicion> res;
    for (int i = 0; i < filas(t); ++i)
        for (int j = 0; j < columnas(t); ++j)
            if (viva(t, i, j)) res.push_back(make_tuple(i, j));
    return res;
}

/***************************** EJERCICIO densidadPoblacion ******************************/
float densidadPoblacion(toroide t) {
    return (float) cantidadDeVivas(t) / superficieTotal(t);
}

/**************************** EJERCICIO evolucionDePosicion *****************************/
bool evolucionDePosicion(toroide t, posicion p) {
    return debeVivir(t, p);
}

/****************************** EJERCICIO evolucionToroide ******************************/
void evolucionToroide(toroide &t) {
    toroide tOriginal = t;
    for (int i = 0; i < filas(t); ++i)
        for (int j = 0; j < columnas(t); ++j)
            t[i][j] = evolucionDePosicion(tOriginal, make_tuple(i, j));
}

/***************************** EJERCICIO evolucionMultiple ******************************/
toroide evolucionMultiple(toroide t, int k) {
    toroide tE = t;
    for (int i = 0; i < k; ++i) evolucionToroide(tE);
    return tE;
}

/******************************** EJERCICIO esPeriodico *********************************/
bool esPeriodico(toroide t, int &p) {
    toroide tE = t;
    vector<toroide> ts;
    int periodo = 0;
    while (true) {
        periodo++;
        evolucionToroide(tE);
        if (tE == t) {
            //alguna evolucion del toroide tE a partir de t volvio a ser igual al original por lo tanto es periodico
            p = periodo;
            return true;
        } else {
            //la evolucion tE no es igual a t, pero busco algun 'subperiodo' dentro de la historia de evoluciones
            //un subperiodo de t es un tE periodico donde tE es alcanzable por k evoluciones desde t pero tE != t
            for (int i = 0; i < ts.size(); ++i) {
                if (ts[i] == tE) {
                    //encontre un 'subperiodo' de tE, es decir tE evolucionara periodicamente y nunca va a llegar al t original
                    //por lo tanto t no es periodico, no existen k evoluciones que lo regresen a si mismo
                    //sino que evoluciona a un tE que loopea en su propio periodo
                    return false;
                }
            }
            //tE no es un subperiodo de alguna evolucion anterior en este punto, lo agrego a la historia de evoluciones y sigo iterando
            ts.push_back(tE);
        }
    }
    //la terminacion del algoritmo se basa en la propiedad que todo toroide es periodico o tiene un subperiodo
    //la idea es que la operacion evolucionToroide esta definida para todo toroide t, luego hay una secuencia infinita de evoluciones de t
    //pero el toroide tiene dimensiones finitas por lo tanto hay finitos estados posibles a los que pueda llegar (2^(columnas*filas))
    //luego deben existir dos toroides tP iguales en la secuencia, si tP = t es periodico si tP != t tiene subperiodo.
}

/******************************* EJERCICIO primosLejanos ********************************/
bool primosLejanos(toroide t1, toroide t2) {
    if (!(filas(t1) == filas(t2) && columnas(t2) == columnas(t1))) return false;
    toroide t = t1;
    while (true) {
        int p;
        if (t == t2) {
            //alguna evolucion t de t1 es igual a t2, por lo tanto son primos lejanos.
            return true;
        } else if (esPeriodico(t, p)) {
            //t no es igual a t2, pero tiene un periodo p. En caso de tener alguna evolucion que sea primo lejano de t2 la puedo encontrar en p pasos
            for (int i = 0; i < p; ++i) {
                //hago p evoluciones de t y me fijo si llego a t2
                evolucionToroide(t);
                if (t == t2) {
                    return true;
                }
            }
            //no es posible llegar a t2 con ninguna evolucion de t, no son primos lejanos.
            return false;
        }
        evolucionToroide(t);
    }
}

/****************************** EJERCICIO seleccionNatural ******************************/
int seleccionNatural(vector<toroide> ts) {
    int indice = 0;
    for (int i = 0; i < ts.size(); ++i) {
        if (elToroideMuere(ts[i])) {
            indice = muereEn(ts[i]) > muereEn(ts[indice]) ? i : indice;
        } else {
            return i;
        }
    }
    return indice;
}

/********************************** EJERCICIO fusionar **********************************/
toroide fusionar(toroide t1, toroide t2) {
    toroide t = t1;
    for (int i = 0; i < filas(t); ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            t[i][j] = viva(t1, i, j) && viva(t2, i, j);
        }
    }
    return t;
}

/****************************** EJERCICIO vistaTrasladada *******************************/
bool vistaTrasladada(toroide t1, toroide t2) {
    if (!(filas(t1) == filas(t2) && columnas(t2) == columnas(t1))) return false;
    for (int tx = 0; tx < filas(t1); ++tx) {
        for (int ty = 0; ty < columnas(t1); ++ty) {

            bool esTrasladada = true;
            for (int i = 0; i < filas(t1); ++i) {
                for (int j = 0; j < columnas(t1); ++j) {
                    esTrasladada = esTrasladada && (viva(t1, i, j) == viva(t2, i + tx, j + ty));
                }
            }
            if (esTrasladada) return true;

        }
    }
    return false;
}

/******************************* EJERCICIO enCrecimiento ********************************/
bool enCrecimiento(toroide t) {
    toroide tE = t;
    evolucionToroide(tE);
    return calcularMinimaSuperficie(t) < calcularMinimaSuperficie(tE);
}

/******************************* EJERCICIO soloBloques (OPCIONAL) ***********************/
bool soloBloques(toroide t) {
    for (int i = 0; i < filas(t); ++i) {
        for (int j = 0; j < columnas(t); ++j) {
            if (viva(t, i, j) && !esBloque(t, i, j)) return false;
        }
    }
    return true;
}
