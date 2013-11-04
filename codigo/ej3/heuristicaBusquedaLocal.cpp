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

pair <int,vector<int> > mejorVecinaQuitando(grafo, s0) { //quito el de menor grado
	fronteraClique = frontera(grafo, s0);
	
	int minimo = grafo.vecindad(s0[0]).size(); //seteo un grado
	int minimoNodo = 0;
	int aux;
	
	for (int i = 1; i < s0.size(); i++){ // calculo cual es el nodo de s0 de menor grado
		aux = grafo.vecindad(s0[i]).size();
		if (aux < minimo){
			minimo = aux
			minimoNodo = i;
		}
	}
	
	vector<int> cliqueQuitando;
	for (int i = 0; i < s0.size(); i++){
		if(minimoNodo != i)
			cliqueQuitando.push_back(s0[i]);
	}
	
	minimo -= (s0.size() - 1); //#aristas de la frontera q aportaba ese nodo
	fronteraClique -= minimo; //quito la #aristas de la frontera q aportaba el nodo eliminado
	fronteraClique += (s0.size() - 1);
	
	pair <int,vector<int> > res;
	res = make_pair (fronteraClique,cliqueQuitando);
	return res;	
}

pair <int,vector<int> > mejorVecinaQuitando(grafo, s0) { //quito el de menor grado
	vector<int> bucket (grafo.nodos(),0); //inicializo un arreglo de n posiciones en 0
	
	for (int i = 0; i < s0.size(); i++) { //marco cuantos nodos de la clique llegan a cada nodo del grafo
		for (int j = 0; j < grafo.vecindad(s0[i]).size(); j++)	{
			int nodo = grafo.vecindad(s0[i])[j];
			bucket[nodo-1]++;
		}
	}
	
	for (int i = 0; i < s0.size(); i++)  //limpio los elementos de la clique
		bucket[s0[i]-1] = 0;
	
	int tamClique = s0.size();
	vector <int> posibleClique;
	
	for (int i = 0; i < grafo.nodos(); i++) //busco a todos los elementos que pueden formar una clique
		if (bucket[i] == tamClique)
			posibleClique.push_back(i+1);		

	int tamFrontera = 0;
	int maxFrontera = 0;
	int nodo;
	
	for (int i = 0; i < posibleClique.size(); i++)	{ //busco al de mayor frontera
		s0.push_back(posibleClique[i]);
		tamFrontera = frontera(grafo, s0);
		s0.pop_back();
		if (tamFrontera > maxFrontera) {
			maxFrontera = tamFrontera;
			nodo = posibleClique[i];
		}		
	}
	
	pair <int,vector<int> > res;
	
	if (posibleClique.size() == 0)
		res = make_pair (0,s0);
	else {
		s0.push_back(nodo);
		res = make_pair (maxFrontera,s0);
		s0.pop_back();
	}
		
	return res;
	
	
	
	
	
}
int main() {
	Grafo grafo = leerInput(cin);
	
	if(grafo.nodos() != 0){
		
		//represento a la clique como un vector de nodos que perteneces a la clique
		vector<int> s0(1,1); //creo la clique con un solo nodo (el 1); todo grafo no vacio tiene por lo menos un nodo
	
		int tamFrontera = frontera(grafo, s0);
		
		while(true){
			pair <int,vector<int> > aux; //mejor vecina 
			pair <int,vector<int> > maximo; //maximo hasta ahora de los vecinos
			int maximaClique = 0; // 0 = no habia cliques; 1 = agregado; 2 = quitando; 3 = permutando
			
			// genero las vecindades y devuelvo la mejor
			maximo = mejorVecinaAgregando(grafo, s0);
			if (maximo.first() != 0)
				maximaClique = 1;
				
			aux = mejorVecinaQuitando(grafo, s0);
			if (aux.first() > maximo.first()){
				maximo = aux;
				maximaClique = 2;
			}
				
			aux = mejorVecinaPermutando(grafo, s0);
			if (aux.first() > maximo.first()){
				maximo = aux;
				maximaClique = 3;
			}
			
			if(maximo.first() > tamFrontera){
				tamFrontera = maximo.first();
				s0 = maximo.second();
			}
			else
				break;
		}	
		//escribirOutput(cout, solucion);

	}
	return 0;
}
