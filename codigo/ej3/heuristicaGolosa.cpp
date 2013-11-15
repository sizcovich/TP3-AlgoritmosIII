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

vector<uint> VectorcliqueMaxima(Grafo grafo){
    vector<uint> cliqueHastaAhora(1,grafo.nodoDeMayorGrado());
    uint fronteraHastaAhora = grafo.frontera(grafo.nodoDeMayorGrado()); //pongo el grado del nodo de mayor grado
	for(uint i = 0; i<grafo.nodos();++i){
        cliqueHastaAhora.push_back(i); //inserto el nodo i
        if(esClique(grafo, cliqueHastaAhora)){ //pregunto si con el elemento insertado forma una clique 
			if(grafo.frontera(cliqueHastaAhora) > fronteraHastaAhora){ //me fijo si la frontera de la nueva clique es mayor que la de la clique sin i
            	fronteraHastaAhora = grafo.frontera(cliqueHastaAhora); //me guardo la nueva frontera
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
		clique = VectorcliqueMaxima(grafo);
		
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
