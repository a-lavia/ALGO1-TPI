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
    toroide tE = t;
    for (int i = 0; i < k; ++i) evolucionToroide(tE);
    return tE;
}

/******************************** EJERCICIO esPeriodico *********************************/
bool esPeriodico(toroide t, int& p){
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
			for (int i = 0; i < ts.size(); ++i) {
				if (ts[i] == tE) {
					//encontre un 'subperiodo' de tE, es decir tE evolucionara periodicamente y nunca va a llegar al t original
					//por lo tanto t no es periodico, no existen k evoluciones que lo regresen a si mismo
					//sino que evoluciona a un tE que loopea en su propio periodo
					return false;
				}
			}
			//tE no tiene un subperiodo, lo agrego a la historia de evoluciones y sigo iterando
			ts.push_back(tE);
		}
	}
	//La terminacion del algoritmo se basa en la propiedad que todo toroide tiene un periodo o un 'subperiodo'
}

/******************************* EJERCICIO primosLejanos ********************************/
bool primosLejanos(toroide t1, toroide t2) {
	toroide t = t1;
	while (true) {
		int p = 0;
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
