#ifndef JUEGODELAVIDA_ES_H
#define JUEGODELAVIDA_ES_H
#include "definiciones.h"

#include <iostream>
#include <fstream>

toroide cargarToroide(string nombreArchivo, bool &status);
bool escribirToroide(string nombreArchivo, toroide &t);

#endif // JUEGODELAVIDA_ES_H
