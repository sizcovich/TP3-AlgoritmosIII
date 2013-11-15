#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <ctgmath>
#include <iterator>
#include "grafo.h"

using namespace std; 

bool esClique(Grafo grafo, vector<uint> clique){
    for (uint i=0; i<clique.size(); ++i) {
        for (uint j=0; j<clique.size(); ++j) {
            if(i != j){
            	if(!grafo.sonVecinos(clique[i],clique[j])) return false;
            }
    	}
    }
    return true;
}

uint nodoDeMayorGradoMio(Grafo grafo){
	uint mayorNodo = 1;
	for(uint i = 1; i<grafo.nodos(); ++i){
		if(grafo.vecindad(i).size()>grafo.vecindad(mayorNodo).size()) mayorNodo = i;
	}
	return mayorNodo;
}

vector<uint> VectorcliqueMaxima(Grafo grafo, uint nodoMayor){
    vector<uint> cliqueHastaAhora;
    cliqueHastaAhora.push_back(nodoDeMayorGradoMio(grafo));
    uint fronteraHastaAhora = 0;
	for(uint i = 0; i<grafo.nodos();++i){
        cliqueHastaAhora.push_back(i); //inserto el nodo i
        if(esClique(grafo, cliqueHastaAhora)){ //pregunto si con elemento insertado forma una clique 
			if(grafo.frontera(cliqueHastaAhora) > fronteraHastaAhora){
            	fronteraHastaAhora = grafo.frontera(cliqueHastaAhora);
        	}else{
                cliqueHastaAhora.pop_back();
            }
        }
	}
	return cliqueHastaAhora;
}


int main() {
	vector<uint> clique;
	int termino = '1';
	while (termino != '0') {
		uint n, m;
		cin >> n >> m;

		Grafo grafo(n);
		for (uint i=0; i<m; i++) {  //O(n²)
			uint i,j;
			cin >> i >> j;
			i--; j--;

			grafo.agregarArista(i, j);
		}
		
		auto t1 = chrono::high_resolution_clock::now();
		clique = VectorcliqueMaxima(grafo, grafo.nodoDeMayorGrado());
		
		cout << grafo.frontera(clique) << " " << clique.size() << " ";
		for (uint i = 0; i < clique.size(); i++) //O(n)
			cout << clique[i] + 1<< " ";
			
		cout << endl;
		
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << n << " " << m << " " << x << endl;
		
		termino = (cin >> ws).peek();
	}
		
	return 0;
}
