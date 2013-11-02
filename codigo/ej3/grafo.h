#ifndef __AED3__GRAFO__
#define __AED3__GRAFO__

#include "common.h"

class Grafo {
		public:
			//Crea un grafo dada su cantidad de nodos.
			Grafo(uint nodos) : 
				vecinos(nodos, vuint()),
				adyacencia(nodos, std::vector<bool>(nodos, false)),
				cnodos(nodos) {
						assert(nodos > 0);
				}
			
			//Cantidad de nodos
			uint nodos() const{
				return cnodos;
			}
			
			//Indica si dos nodos son vecinos
			bool sonVecinos(uint v, uint w) const{
				assert(v >= 0 && v < nodos());
				assert(w >= 0 && w < nodos());

				return adyacencia[v][w];
			}

			//Agrega una arista no dirigida entre inicio y fin.
			void agregarArista(uint inicio, uint fin){
				assert(inicio >= 0 && inicio < nodos());
				assert(fin >= 0 && fin < nodos());
				assert(inicio != fin);

				vecinos[inicio].push_back(fin);
				vecinos[fin].push_back(inicio);
				adyacencia[inicio][fin] = adyacencia[fin][inicio] = true;
			}

			//Devuelve los vecinos de un nodo.
			const vuint& vecindad(uint nodo) const{
				assert(nodo >= 0 && nodo < nodos());
				return vecinos[nodo];
			}				
				
				
		private:				
			//La representacion del grafo es por lista de vecinos y además matriz de adyacencia, para tener la op. sonVecinos en O(1)
			std::vector< vuint > vecinos;
			std::vector<std::vector<bool> > adyacencia;
			uint cnodos;
};

#endif
