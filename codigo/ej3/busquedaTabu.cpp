#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <list>
#include <queue>
#include <ctgmath>
#include "grafo.h"

using namespace std; 

// EMPIEZO A CONTAR LOS NODOS DE 0

//lista tabu: restringe nodos
vector<bool> listabu;
//evita entrar en un ciclo infinito de borrar y agregar
int ultimoAgregado = 0;

class solucionTabu
{
public:
	vector<bool> esta; // pone 1 en la iesima posicion si el nodo se encuentra y 0 en otro caso.
	list<uint> adentro; //contiene los nodos pertenecientes a la solucion
	list<uint> candidato; //contiene los nodos candidatos a formar una clique con la solucion inicial
	uint cantFrontera; //tiene el tamaño de la frontera para la solucion actual

	solucionTabu(Grafo& g, vector<uint>& solInicial)
	{
		cantFrontera = 0;
		//inicializo el estado de los nodos	
		for (int i=0;i<g.nodos();++i)
			esta.push_back(false);
		// guardo adentro la solucion inicial
		for (int i=0;i<solInicial.size();++i)
			adentro.push_back(solInicial[i]);
		
		for (vector<uint>::iterator it=solInicial.begin(); it != solInicial.end(); ++it)
		{
			//actualizo estados
			esta[ *it ] = true; 
			//guardo grados de nodos
			cantFrontera += g.vecindad( *it ).size();
			for (vector<uint>::iterator it2=it; it2 != solInicial.end(); ++it2)
			{		
				if (g.sonVecinos(*it,*it2))
					--cantFrontera;
			}
		}
		for (uint i=0;i<g.nodos();++i)
		{
			bool estaEnClique = true;
			for (list<uint>::iterator it=adentro.begin(); it != adentro.end()  && estaEnClique; ++it)
			{
				estaEnClique &= g.sonVecinos(i,*it); 
			}
			if (estaEnClique)
				candidato.push_back(i);
		}
		
	}

	vector<uint> toVec()
	{
		vector<uint> salida{ make_move_iterator( begin(adentro) ), make_move_iterator( end(adentro) ) };
		return (salida);
	}
};


/* ----------------------------------------------------
	Quita el nodo "n" de l solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu& quitarNodo(uint n, solucionTabu& solucion, Grafo& g)
{
	solucionTabu salida = solucion;
	salida.esta[n] = false;
	salida.adentro.remove(n);
	//calculo nueva frontera
	int adentro = 0;
	for (list<uint>::iterator it=solucion.adentro.begin(); it != solucion.adentro.end() ; ++it)
	{
		if (g.sonVecinos(n,*it))
			++adentro; 
	}
	int afuera = g.vecindad(n).size() - adentro;
	salida.cantFrontera = salida.cantFrontera - afuera + adentro; 
}

/* ----------------------------------------------------
	Agrega el nodo "n" a la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu& agregarNodo(uint n, solucionTabu& solucion, Grafo& g)
{
	solucionTabu salida = solucion;
	salida.esta[n] = true;
	salida.adentro.push_back(n);
	//calculo nueva frontera
	bool estaEnClique = true;
	int adentro = 0;
	for (list<uint>::iterator it=solucion.adentro.begin(); it != solucion.adentro.end() ; ++it)
	{
		if (g.sonVecinos(n,*it))
			++adentro; 
	}
	int afuera = g.vecindad(n).size() - adentro;
	salida.cantFrontera = salida.cantFrontera - adentro + afuera;
	listabu[n] = false;
}

/* --------------------------------------------------

	Calcula la cardinalidad de la frontera de g
	Complejidad:

----------------------------------------------------- */

uint cantFrontera(solucionTabu& sol )
{
	return (sol.cantFrontera);
}


/* ---------------------------------------------------

	Tabu Search

------------------------------------------------------ */

vector<uint> tabuSearch(vector<uint>& solIni, Grafo& g)
{
	uint seguir = 10; 			//cantidad de pasos
	uint desviacion_permitida = 30 ;	// cantidad de iteraciones maximas en las que va a disminuir
	listabu.clear();
	for(int i=0;i<g.nodos();++i)
		listabu.push_back(true);				

	uint desciacion_faltante = desviacion_permitida+1; 
	solucionTabu solInicial(g,solIni); 	//solucion inicial
	solucionTabu gt_mejor(g,solIni);   	//mejor solucion
	ultimoAgregado = g.nodos()+1;		
	bool descender = false;
	while (0<seguir) // Seguro lo va a hacer hasta llegar a un minimo local
	{
		uint ultimoMejor = cantFrontera(gt_mejor);
		do{
			for (list<uint>::iterator it=solInicial.candidato.begin(); it != solInicial.candidato.end(); ++it)
			{
				if (!solInicial.esta[*it] && listabu[*it] && (ultimoAgregado - *it != 0))
				{
					uint fronteraAgregar = cantFrontera( agregarNodo(*it,gt_mejor,g) );
					if (cantFrontera(gt_mejor)<fronteraAgregar)
					{
						gt_mejor = agregarNodo(*it,gt_mejor,g);
						ultimoAgregado = *it;
					}
				}	
			}
			for (list<uint>::iterator it=solInicial.adentro.begin(); it != solInicial.adentro.end(); ++it)
			{
				if ( listabu[*it] && (ultimoAgregado - *it != 0))
				{
					uint fronteraQuitar = cantFrontera( quitarNodo(*it,solInicial,g));		
					if (cantFrontera(gt_mejor)<fronteraQuitar )
					{
						gt_mejor = quitarNodo(*it,solInicial,g);
						ultimoAgregado = *it * -1;
					}
				}
			}
		}while(0<descender);
		solInicial = gt_mejor;
		//permito descender de manera aleatoria siempre acotado por desviacion_permitida
		descender = rand()%(desciacion_faltante);
		desciacion_faltante -= descender;
	}
	return ( gt_mejor.toVec() );

}

int main() {

	return 0;
}
