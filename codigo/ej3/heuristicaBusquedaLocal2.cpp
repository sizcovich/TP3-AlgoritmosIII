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

/*
uint nodoDeMayorGrado(Grafo grafo){
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
	for(int i = 1; i<clique.size(); ++i){
		res = res + grafo.vecindad(clique[i]).size();
	}
	return res-clique.size()*(clique.size()-1);
}
*/

pair<uint,vector<uint> > mejorVecinaQuitando(Grafo grafo, vector<uint> clique) { //quito el de menor grado
	uint fronteraClique = grafo.frontera(clique);
	
	uint minimo = grafo.vecindad(clique[0]).size(); //seteo un grado
	uint minimoNodo = 0;
	uint aux;
	
	for (uint i = 1; i < clique.size(); i++){ // calculo cual es el nodo de clique de menor grado
		aux = grafo.vecindad(clique[i]).size();
		if (aux < minimo){
			minimo = aux;
			minimoNodo = i;
		}
	}
	
	vector<uint> cliqueQuitando;
	for (uint i = 0; i < clique.size(); i++){
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
	
	for (uint i = 0; i < clique.size(); i++) { //marco cuantos nodos de la clique llegan a cada nodo del grafo
		for (uint j = 0; j < grafo.vecindad(clique[i]).size(); j++)	{
			uint nodo = grafo.vecindad(clique[i])[j];
			bucket[nodo-1]++;
		}
	}
	
	for (uint i = 0; i < clique.size(); i++)  //limpio los elementos de la clique
		bucket[clique[i]-1] = 0;
	
	uint tamClique = clique.size();
	vector <uint> posibleClique;
	
	for (uint i = 0; i < grafo.nodos(); i++) //busco a todos los elementos que pueden formar una clique
		if (bucket[i] == tamClique)
			posibleClique.push_back(i+1);		

	uint tamFrontera = 0;
	uint maxFrontera = 0;
	uint nodo;
	
	for (uint i = 0; i < posibleClique.size(); i++)	{ //busco al de mayor frontera
		clique.push_back(posibleClique[i]);
		tamFrontera = grafo.frontera(clique);
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
	pair <uint,vector<uint> > aux;
	
	res = make_pair (grafo.frontera(clique),clique); //O(n)
	
	for (int i = 0; i < clique.size(); i++){ //O(n³)
		vector<uint> cliqueQuitando;
		for (uint j = 0; j < clique.size(); j++){ //O(n)
			if(i != j)
				cliqueQuitando.push_back(clique[j]);
		}
	
		aux = mejorVecinaAgregando(grafo, cliqueQuitando);  //O(n²)
		if (aux.first > res.first)
			res = aux;
	}
	
	
	return res;
}

int main() {
	
	int termino = '1';
	while (termino != '0') {
		Grafo grafo = leerInput(cin);
	
		//represento a la clique como un vector de nodos que perteneces a la clique
		vector<uint> clique(1,1); //creo la clique con un solo nodo (el 1); todo grafo no vacio tiene por lo menos un nodo

		uint tamFrontera = grafo.frontera(clique);
		
		while(true){
			pair <uint,vector<uint> > aux; //mejor vecina 
			pair <uint,vector<uint> > maximo; //maximo hasta ahora de los vecinos
		
			// genero las vecindades y devuelvo la mejor
			maximo = mejorVecinaAgregando(grafo, clique); //O(n²)
							
			aux = mejorVecinaQuitando(grafo, clique); //O(n)
			if (aux.first > maximo.first)
				maximo = aux;
				
			aux = mejorVecinaPermutando(grafo, clique);  //O(n³)
			if (aux.first > maximo.first)
				maximo = aux;
			
			if(maximo.first > tamFrontera){
				tamFrontera = maximo.first;
				clique = maximo.second;
			}
			else
				break;
		}
		
		cout << tamFrontera << " " << clique.size() << " ";
		for (int i = 0; i < clique.size(); i++)
			cout << clique[i] << " ";
			
		cout << endl;
		
		termino = (cin >> ws).peek();
	}
		
	return 0;
}
