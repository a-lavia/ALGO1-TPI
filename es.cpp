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
	int cantidadDeVivas = 0;
	ofstream fout;
	fout.open(nombreArchivo);
	if(fout.fail()){
		return false;
	}
	fout << t.size() << ' ';
	fout << t[0].size() << endl;

	for (int i = 0; i < t.size() ; ++i) {
		for (int j = 0; j <t[0].size() ; ++j) {
			 if(t[i][j] == true){
				 fout << 1;
				 cantidadDeVivas ++;
			 } else fout << 0;
			if (j < t[0].size()-1) fout << ' ';
		}
   		fout << endl;
	}
	fout << cantidadDeVivas << endl;
	fout.close();
	if(fout.fail()){
		return false;
	}
	return true;
}
