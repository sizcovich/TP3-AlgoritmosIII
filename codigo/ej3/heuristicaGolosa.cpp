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


uint nodoDeMayorGrado(Grafo grafo){
	uint mayorNodo = 1;
	for(uint i = 1; i<grafo.nodos(); ++i){
		if(grafo.vecindad(i).size()>grafo.vecindad(mayorNodo).size()) mayorNodo = i;
	}
	return mayorNodo;
}

Grafo cliqueMaxima(Grafo grafo, uint nodoMayor){
	for(uint i = 1; i<grafo.vecindad(nodoMayor).size();++i){
		//if(frontera(agregarNodo))
	}

}

uint frontera(Grafo grafo, vector<uint> clique){
	uint res = 0;
	for(uint i = 0; i<clique.size(); ++i){
		res = res + grafo.vecindad(clique[i]).size();
	}
	return res-clique.size()*(clique.size()-1);
}

int main() {

	return 0;
}
