#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <queue>
#include <ctgmath>

using namespace std; 


class Grafo leerInput(istream&);
//void escribirOutput(ostream&, const vuint&);

Grafo leerInput(istream& is) {
	uint n, m;
	is >> n >> m;

	Grafo grafo(n);
	FORN(k, m) {
		uint i,j;
		is >> i >> j;
		i--; j--;

		grafo.agregarArista(i, j);
	}

	return grafo;
}

//ordeno los nodos de acuerdo a su grado
//elijo el de mayor grado y lo agrego
//tomo alguno de los adyacentes de ese nodo

void ordenarNodos()

int main() {

	return 0;
}
