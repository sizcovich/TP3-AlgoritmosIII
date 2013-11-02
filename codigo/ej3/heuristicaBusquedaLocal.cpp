#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <queue>
#include <ctgmath>
#include "grafo.h"

using namespace std; 


class Grafo leerInput(istream&);
void escribirOutput(ostream&, const vuint&);

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

void escribirOutput(ostream& os, const vuint& solucion) {
	os << solucion.size() << endl;
	FORN(i, solucion.size())
		os << (solucion[i]+1) << " ";
	cout << endl;
}

int main() {
	Grafo grafo = leerInput(cin);
	
	if(grafo.nodos() != 0){
		
		//represento a la clique como un vector de nodos que perteneces a la clique
		vector<int> s0(1,1); //creo la clique con un solo nodo (el 1); todo grafo no vacio tiene por lo menos un nodo
		vector<int> cliqueAgregando;
		vector<int> cliqueQuitando;
		vector<int> cliquePermutando;
		
		int tamFrontera = frontera(grafo, s0);
		
		while(true){
			int aux = 0; //mejor vecina 
			int maximo = 0; //maximo hasta ahora de los vecinos
			int maximaClique = 0; // 0 = no habia cliques; 1 = agregado; 2 = quitando; 3 = permutando
			
			// genero las vecindades y devuelvo la mejor
			maximo = mejorVecinaAgregando(grafo, s0, cliqueAgregando);
			if (maximo != 0)
				maximaClique = 1;
				
			aux = mejorVecinaQuitando(grafo, s0, cliqueQuitando);
			if (aux > maximo){
				maximo = aux;
				maximaClique = 2;
			}
				
			aux = mejorVecinaPermutando(grafo, s0, cliquePermutando);
			if (aux > maximo){
				maximo = aux;
				maximaClique = 3;
			}
			
			if(maximo > tamFrontera){
				tamFrontera = maximo;
				switch (maximaClique)
				{
					case 1:
						s0 = cliqueAgregando;
						break;
					
					case 2:
						s0 = cliqueQuitando;
						break;	
						
					default:
						s0 = cliquePermutando;
				}
			}
			else
				break;
		}	
		//escribirOutput(cout, solucion);

	}
	return 0;
}
