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

int frontera=0;


pair<uint,vector<uint> > quitarNodo(const Grafo& grafo, vector<uint> clique) { //quito el de menor grado
	uint fronteraClique = grafo.frontera(clique);//O(n)
	
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

pair <uint,vector<uint> > agregarNodo(const Grafo& grafo, vector<uint> clique) { 
	vector<uint> bucket (grafo.nodos(),0); //inicializo un arreglo de n posiciones en 0
	
	for (uint i = 0; i < clique.size(); i++) { //marco cuantos nodos de la clique llegan a cada nodo del grafo //O(n²)
		for (uint j = 0; j < grafo.vecindad(clique[i]).size(); j++)	{
			uint nodo = grafo.vecindad(clique[i])[j];
			bucket[nodo]++;
		}
	}
	
	for (uint i = 0; i < clique.size(); i++)  //limpio los elementos de la clique //O(n)
		bucket[clique[i]] = 0;
	
	uint tamClique = clique.size();
	vector <uint> posibleClique;
	
	for (uint i = 0; i < grafo.nodos(); i++) //busco a todos los elementos que pueden formar una clique //O(n)
		if (bucket[i] == tamClique)
			posibleClique.push_back(i);		

	uint tamFrontera = 0;
	uint maxFrontera = 0;
	uint nodo;
	
	for (uint i = 0; i < posibleClique.size(); i++)	{ //busco al de mayor frontera //O(n²)
		clique.push_back(posibleClique[i]);
		tamFrontera = grafo.frontera(clique); //O(n)
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

pair<uint,vector<uint> > permutarNodo(const Grafo& grafo, vector<uint> clique){
	pair <uint,vector<uint> > res;
	
	vector<uint> cliqueResultante = quitarNodo(grafo, clique).second;
	
	if (cliqueResultante.size() == 0) { //si esta vacio tomo el de mayor grado de sus vecinos //O(n)
		uint maxFrontera = 0;
		uint nodo = 0;
		for (int i = 0; i < grafo.vecindad(clique[0]).size(); i++)	{
			nodo = grafo.vecindad(clique[0])[i];
			uint tamFrontera = grafo.vecindad(nodo).size();
			if (tamFrontera > maxFrontera) {
				maxFrontera = tamFrontera;
				nodo = grafo.vecindad(clique[0])[i];
			}			
		}
		
		vector<uint> s1(1,nodo);
		res = make_pair (maxFrontera, s1);
		return res;
	}
	
	return agregarNodo(grafo, cliqueResultante); //O(n²)
}

vector<uint> busquedaLocal(const Grafo& grafo, const uint m) { 
		//represento a la clique como un vector de nodos que perteneces a la clique
		vector<uint> clique(1,grafo.nodoDeMayorGrado()); //creo la clique con un solo nodo (el de mayor grado); todo grafo no vacio tiene por lo menos un nodo
	
		uint tamFrontera = grafo.frontera(clique); //O(n)
		
		
		for (int j = 0; j < m; j++)	{
			pair <uint,vector<uint> > aux; //mejor vecina 
			pair <uint,vector<uint> > maximo; //maximo hasta ahora de los vecinos
		
			// genero las vecindades y devuelvo la mejor
			maximo = agregarNodo(grafo, clique); //O(n²)
					
					
			aux = quitarNodo(grafo, clique); //O(n)
			if (aux.first > maximo.first)
				maximo = aux;
				
			aux = permutarNodo(grafo, clique);  //O(n²)
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
		frontera = tamFrontera;
		for (int i = 0; i < clique.size(); i++) //O(n)
			cout << clique[i] + 1<< " ";
			
		cout << endl;
		return clique;
}
int main() {	

	int termino = '1';
	while (termino != '0') {
		uint n, m;
		cin >> n >> m;

		Grafo grafo(n);
		for (int k=0; k<m; k++) {  //O(n²)
			uint i,j;
			cin >> i >> j;
			i--; j--;

			grafo.agregarArista(i, j);
		}
		
		auto t1 = chrono::high_resolution_clock::now();
		for (int i = 0; i < 10; ++i)
		{
			vector <uint> res = busquedaLocal(grafo, m);
		}
		
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << frontera << " " << n << " " << m << " " << (x/10) << endl;
		
		termino = (cin >> ws).peek();
	}
	return 0;
}
