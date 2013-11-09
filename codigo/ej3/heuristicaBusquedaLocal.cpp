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

uint nodoDeMayorGrado(Grafo grafo){ //O(n)
	uint mayorNodo = 1;
	for(uint i = 1; i<grafo.nodos(); ++i){
		if(grafo.vecindad(i).size()>grafo.vecindad(mayorNodo).size()) mayorNodo = i;
	}
	return mayorNodo;
}

uint frontera(Grafo grafo, vector<uint> clique){ //O(n)
	uint res = 0;
	for(int i = 1; i<clique.size(); ++i){
		res = res + grafo.vecindad(clique[i]).size();
	}
	return res-clique.size()*(clique.size()-1);
}

pair<uint,vector<uint> > mejorVecinaQuitando(Grafo grafo, vector<uint> clique) { //quito el de menor grado
	uint fronteraClique = frontera(grafo, clique);//O(n)
	
	uint minimo = grafo.vecindad(clique[0]).size(); //seteo un grado
	uint minimoNodo = 0;
	uint aux;
	
	for (uint i = 1; i < clique.size(); i++){ // calculo cual es el nodo de clique de menor grado //O(n)
		aux = grafo.vecindad(clique[i]).size();
		if (aux < minimo){
			minimo = aux;
			minimoNodo = i;
		}
	}
	
	vector<uint> cliqueQuitando;
	for (uint i = 0; i < clique.size(); i++){ //O(n)
		if(minimoNodo != i)
			cliqueQuitando.push_back(clique[i]);
	}
	
	minimo -= (clique.size() - 1); //#aristas de la frontera q aportaba ese nodo
	fronteraClique -= minimo; //quito la #aristas de la frontera q aportaba el nodo eliminado
	fronteraClique += (clique.size() - 1);
	
	pair <uint,vector<uint> > res;
	res = make_pair (fronteraClique,cliqueQuitando);
	return res;	
}

pair <uint,vector<uint> > mejorVecinaAgregando(Grafo grafo, vector<uint> clique) { 
	vector<uint> bucket (grafo.nodos(),0); //inicializo un arreglo de n posiciones en 0
	
	for (uint i = 0; i < clique.size(); i++) { //marco cuantos nodos de la clique llegan a cada nodo del grafo //O(n²)
		for (uint j = 0; j < grafo.vecindad(clique[i]).size(); j++)	{
			uint nodo = grafo.vecindad(clique[i])[j];
			bucket[nodo-1]++;
		}
	}
	
	for (uint i = 0; i < clique.size(); i++)  //limpio los elementos de la clique //O(n)
		bucket[clique[i]-1] = 0;
	
	uint tamClique = clique.size();
	vector <uint> posibleClique;
	
	for (uint i = 0; i < grafo.nodos(); i++) //busco a todos los elementos que pueden formar una clique //O(n)
		if (bucket[i] == tamClique)
			posibleClique.push_back(i+1);		

	uint tamFrontera = 0;
	uint maxFrontera = 0;
	uint nodo;
	
	for (uint i = 0; i < posibleClique.size(); i++)	{ //busco al de mayor frontera //O(n²)
		clique.push_back(posibleClique[i]);
		tamFrontera = frontera(grafo, clique); //O(n)
		clique.pop_back();
		if (tamFrontera > maxFrontera) {
			maxFrontera = tamFrontera;
			nodo = posibleClique[i];
		}		
	}
	
	pair <uint,vector<uint> > res;
	
	if (posibleClique.size() == 0)
		res = make_pair (0,clique);
	else {
		clique.push_back(nodo);
		res = make_pair (maxFrontera,clique);
		clique.pop_back();
	}
		
	return res;
}

pair<uint,vector<uint> > mejorVecinaPermutando(Grafo grafo, vector<uint> clique) { 
	pair <uint,vector<uint> > res;
	
	if (clique.size() == 0) { //si esta vacio tomo el de mayor grado (no se si esto esta bien) //O(n)
		uint nodo = nodoDeMayorGrado(grafo); //O(n)
		vector<uint> s1(1,nodo);
		res = make_pair (grafo.vecindad(nodo).size(), s1);
		return res;
	}
	
	return mejorVecinaAgregando(grafo, clique); //O(n²)
}

int main() {
	Grafo grafo = leerInput(cin);
	
	if(grafo.nodos() != 0){
		
		//represento a la clique como un vector de nodos que perteneces a la clique
		vector<uint> clique(1,1); //creo la clique con un solo nodo (el 1); todo grafo no vacio tiene por lo menos un nodo
	
		uint tamFrontera = frontera(grafo, clique); //O(n)
		
		while(true){
			pair <uint,vector<uint> > aux; //mejor vecina 
			pair <uint,vector<uint> > maximo; //maximo hasta ahora de los vecinos
		
			// genero las vecindades y devuelvo la mejor
			maximo = mejorVecinaAgregando(grafo, clique); //O(n²)
							
			aux = mejorVecinaQuitando(grafo, clique); //O(n)
			if (aux.first > maximo.first)
				maximo = aux;
				
			aux = mejorVecinaPermutando(grafo, aux.second); //paso la solucion de mejorvecinaQuitando; puede ser la clique con un elemento menos o una clique vacia. Saco el nodo q menos aporta y agrego un nuevo nodo. //O(n²)
			if (aux.first > maximo.first)
				maximo = aux;
			
			if(maximo.first > tamFrontera){
				tamFrontera = maximo.first;
				clique = maximo.second;
			}
			else
				break;
		}	
		//escribirOutput(cout, solucion);

	}
	return 0;
}
