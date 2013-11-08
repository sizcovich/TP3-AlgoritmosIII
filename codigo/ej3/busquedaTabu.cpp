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

void mezclar(list<uint>& lista)
{
	vector<uint> vetor( lista.begin(), lista.end() );
	random_shuffle( vetor.begin(), vetor.end() ); //http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	list<uint> lista_new( vetor.begin(), vetor.end() );
	lista = lista_new;
}

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
		mezclar(candidato);
		
	}

	vector<uint> toVec()
	{
		vector<uint> salida{ make_move_iterator( begin(adentro) ), make_move_iterator( end(adentro) ) };
		return (salida);
	}
};


/* ----------------------------------------------------
	Quita el nodo "n" de la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu& quitarNodo(uint n, solucionTabu& solucion, Grafo& g)
{
	if (solucion.candidato.size() == 0) //si los candidatos antes eran todos ahora tengo que quedarme con los corrector (alcanza con hacer esto solo con el primer nodo de la lista)
	{
		for (uint i=0;i<g.nodos();++i)
		{ 
				solucion.candidato.push_back(i);
		}
		mezclar(solucion.candidato); //Esto es para darle aleatoridad a las decisiones
	}
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
	if (solucion.candidato.size() == g.nodos()) //si los candidatos antes eran todos ahora tengo que quedarme con los corrector (alcanza con hacer esto solo con el primer nodo de la lista)
	{
		for (uint i=0;i<g.nodos();++i)
		{ 
			if (g.sonVecinos(i,n))
				solucion.candidato.push_back(i);
		}
		mezclar(solucion.candidato); //Esto es para darle aleatoridad a las decisiones
	}
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

	En la primera iteracion ("seguir"=1) encuentra un maximo local. Esto lo hace buscando el maximo entre quitar o agregar nodos pertenecientes a la clique de la solucion inicial. (La vecindad esta dada por cliques con mas, o menos, un nodo de la clique actual ).
	Una vez alcanzado el maximo local realiza "seguir-1" iteraciones donde desciende del maximo local hasta "desviacion_permitida" (donde cada descenso esta dado por agregar o quitar un nodo que no mejora la frontera). Por cada iteracion (desde la segunda hasta la "seguir") limpia la lista tabu y va agregando los ultimos dos nodos agregados a la solucion parcial, permitiendo asi quitar los primeros o agregar nuevos en busca de mejores soluciones. 

------------------------------------------------------ */

vector<uint> tabuSearch(vector<uint>& solIni, Grafo& g, uint cant_pasos, uint desviacion_permitida)
{
	listabu.clear();
	for(int i=0;i<g.nodos();++i)
		listabu.push_back(true);				
	solucionTabu gt_inicial(g,solIni); 	//solucion inicial
	solucionTabu gt_mejor(g,solIni);   	//mejor solucion
	solucionTabu gt_actual(g,solIni);   	//mejor solucion
	ultimoAgregado = g.nodos()+1;		
	int descender = 0; //empieza en 0 porque primero quiero llegar a un maximo local

	while (0<cant_pasos)
	{

		uint cantFrontera_ini;
		do{ // Busca el maximo local
			cantFrontera_ini = cantFrontera(gt_inicial);

			int i=0;
			for (list<uint>::iterator it=gt_inicial.candidato.begin(); it != gt_inicial.candidato.end(); ++it)
			{
				if (!gt_inicial.esta[*it] && listabu[*it])
				{
					uint fronteraAgregar = cantFrontera( agregarNodo(*it,gt_inicial,g) );
					bool asciende = cantFrontera(gt_mejor) < fronteraAgregar; 					
					if (asciende)
					{
						gt_mejor = agregarNodo(*it,gt_mejor,g);
						listabu[*it] = false;
					}
					if (descender>0 && !asciende) //desciendo un poco la solucion cuando ya no puedo subir
					{
						gt_inicial = agregarNodo(*it,gt_inicial,g);
						listabu[*it] = false;
						--descender;
					}
					++i;
				}	
			}

			i=0;
			for (list<uint>::iterator it=gt_inicial.adentro.begin(); it != gt_inicial.adentro.end(); ++it)
			{
				if ( listabu[*it] )
				{
					uint fronteraQuitar = cantFrontera( quitarNodo(*it,gt_inicial,g));
					bool asciende = cantFrontera(gt_mejor) < fronteraQuitar; 		
					if (asciende)
					{
						gt_mejor = quitarNodo(*it,gt_inicial,g);
						listabu[*it] = false;
					}
					if (descender>0 && !asciende) //desciendo un poco la solucion cuando ya no puedo subir
					{
						gt_inicial = agregarNodo(*it,gt_inicial,g);
						listabu[*it] = false;
						--descender;
					}
					++i;
				}
			}
			if (descender<=0)
				gt_inicial = gt_mejor;

		}while(cantFrontera_ini < cantFrontera(gt_mejor) || descender>0); //paro cuando no mejora la solucion o no puedo descender mas

		//permito descender de manera aleatoria siempre acotado por desviacion_permitida
		descender = desviacion_permitida;
		//modifico lista tabu
		for(int i=0;i<listabu.size();++i) //permito todos los anteriores tabu
			listabu[i]=true;
		list<uint>::iterator ultimo = gt_inicial.adentro.end();
		if (!gt_inicial.adentro.empty()) //por si no hay un elemento en la solucion
			listabu[*ultimo] = false;
		if (ultimo != gt_inicial.adentro.begin()) //por si hay un elemento solo en la solucion
			listabu[*(--ultimo)] = false;

		--cant_pasos;
	}

	return ( gt_mejor.toVec() );

}

int main() {

	uint cant_pasos = 10; 			//cantidad de pasos, con seguir=1 encuentra el maximo local.
	uint desviacion_permitida = 30 ;	// cantidad de iteraciones maximas en las que va a disminuir
		

	return 0;
}
