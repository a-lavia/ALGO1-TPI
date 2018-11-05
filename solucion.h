#ifndef JUEGODELAVIDA_SOLUCION_H
#define JUEGODELAVIDA_SOLUCION_H
#include "definiciones.h"

bool esValido(toroide t);
vector<posicion> posicionesVivas(toroide t);
float densidadPoblacion(toroide t);
int cantidadBloques(toroide t);
bool evolucionDePosicion(toroide t, posicion p);
void evolucionToroide(toroide& t);
toroide evolucionMultiple(toroide t, int k);
bool esPeriodico(toroide t, int& p);
bool primosLejanos(toroide t1, toroide t2);
int seleccionNatural(vector<toroide> ts);
toroide fusionar(toroide t1, toroide t2);
bool vistaTrasladada(toroide t1, toroide t2);
void cercarCelulasVivas(toroide& t);
bool enCrecimiento(toroide t);
bool soloBloques(toroide t);

#endif //JUEGODELAVIDA_SOLUCION_H
