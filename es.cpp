#include "es.h"
#include <iostream>
#include <fstream>
#include "definiciones.h"

/******************************** EJERCICIO cargarToroide *******************************/
toroide cargarToroide(string nombreArchivo, bool &status)
{

	int cantidadFilas;
	int cantidadColumnas;
	toroide t;
	ifstream fin;
	fin.open(nombreArchivo, ifstream::in);

	if (fin.fail()) {
		status = false;
		return t;
	}

	fin >> cantidadFilas;
	fin >> cantidadColumnas;
	int contadorVivas = 0;
	for (int i = 0; i < cantidadFilas; ++i) {
		t.push_back(vector<bool>(cantidadColumnas, false));
		for (int j = 0; j < cantidadColumnas; ++j) {
			int celda;
			fin >> celda;
			if (celda == 1) {
				t[i][j] = true;
				contadorVivas++;
			} else if(celda == 0) {
				t[i][j] = false;
			} else {
				status = false;
				return t;
			}
		}
	}
	int cantidadVivas;
	fin >> cantidadVivas;
	status = (cantidadVivas == contadorVivas);
	fin.close();

	return t;
}


/******************************** EJERCICIO escribirToroide *****************************/
bool escribirToroide(string nombreArchivo, toroide &t)
{
	bool res;
	return res;
}
