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


/*uint nodoDeMayorGrado(Grafo grafo){
	uint mayorNodo = 1;
	for(uint i = 1; i<grafo.nodos(); ++i){
		if(grafo.vecindad(i).size()>grafo.vecindad(mayorNodo).size()) mayorNodo = i;
	}
	return mayorNodo;
}
*/

/*
uint frontera(Grafo grafo, vector<uint> clique){
	uint res = 0;
	for(uint i = 1; i<clique.size(); ++i){
		res = res + grafo.vecindad(clique[i]).size();
	}
	return res-clique.size()*(clique.size()-1);
}
*/

bool esClique(Grafo grafo, vector<uint> clique){
    for (uint i=1; i<clique.size(); ++i) {
        for (uint j=1; j<clique.size(); ++j) {
            if(clique[i] != clique[j]){
            	if(!grafo.sonVecinos(clique[i],clique[j])) return false;
            }
    	}
    }
    return true;
}

vector<uint> VectorcliqueMaxima(Grafo grafo, uint nodoMayor){
    vector<uint> cliqueHastaAhora;
    uint fronteraHastaAhora = 0;
	for(uint i = 1; i<grafo.vecindad(nodoMayor).size();++i){
        cliqueHastaAhora.push_back(i);
        if(esClique(grafo, cliqueHastaAhora)){
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

	return 0;
}
