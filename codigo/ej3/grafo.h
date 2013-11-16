#ifndef __AED3__GRAFO__
#define __AED3__GRAFO__

#include "common.h"

class Grafo {
		public:
			//Crea un grafo dada su cantidad de nodos.
			Grafo(uint nodos) : 
				vecinos(nodos, vuint()), //O(n)
				adyacencia(nodos, std::vector<bool>(nodos, false)), //O(n²)
				cnodos(nodos) { //O(1)
				}
			
			//Cantidad de nodos
			uint nodos() const{ //O(1)
				return cnodos;
			}
			
			//Indica si dos nodos son vecinos
			bool sonVecinos(uint v, uint w) const{ //O(1)
				return adyacencia[v][w];
			}

			//Agrega una arista no dirigida entre inicio y fin.
			void agregarArista(uint inicio, uint fin){ //O(1)
				vecinos[inicio].push_back(fin);
				vecinos[fin].push_back(inicio);
				adyacencia[inicio][fin] = adyacencia[fin][inicio] = true;
			}

			//Devuelve los vecinos de un nodo.
			const vuint& vecindad(uint nodo) const{ //O(1)
				return vecinos[nodo];
			}				
			
			//Devuelve el nodo de mayor grado o 0 si el grafo es vacio
			uint nodoDeMayorGrado(){ //O(n)
				if (vecinos.empty())
					return 0;
					
				uint mayorNodo = 0;
				for(uint i = 1; i<cnodos; i++){ //O(n)
					if(vecinos[i].size()>vecinos[mayorNodo].size()) mayorNodo = i; //O(1) pues usa vector
				}
				return mayorNodo;
			}	
			
			//Devuelve el valor de la frontera de la clique pasada por parametro
			uint frontera(vuint clique){ //O(n)
				uint res = 0;
				for(uint i = 0; i<clique.size(); i++){ //O(n)
					res = res + vecinos[clique[i]].size(); //O(1) porque usa vector
				}
				return res-clique.size()*(clique.size()-1);
			}
			
			
		private:				
			//La representacion del grafo es por lista de vecinos y además matriz de adyacencia, para tener la op. sonVecinos en O(1)
			std::vector< vuint > vecinos;
			std::vector<std::vector<bool> > adyacencia;
			uint cnodos;
};

#endif
