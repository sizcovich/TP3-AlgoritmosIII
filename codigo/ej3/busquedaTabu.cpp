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
vector<int> listabu;
int maxValorTabu;

class solucionTabu
{
public:
	vector<bool> esta; // pone 1 en la iesima posicion si el nodo se encuentra y 0 en otro caso.
	list<uint> adentro; //contiene los nodos pertenecientes a la solucion
	list<uint> candidato; //contiene los nodos candidatos a formar una clique con la solucion inicial
	uint cantFrontera; //tiene el tamaño de la frontera para la solucion actual

	solucionTabu(Grafo& g)
	{
		cantFrontera = 0;
		//inicializo el estado de los nodos	
		for (int i=0;i<g.nodos();++i){
			esta.push_back(false);
			candidato.push_back(i);}
		
	}

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

	bool operator ==(const solucionTabu &p2)
	{
		return(this->esta == p2.esta && this->adentro==p2.adentro && this->candidato==p2.candidato && this->cantFrontera==p2.cantFrontera);
	}


};

	ostream& operator << (ostream &o,solucionTabu &p)
	{
	    o << "Nodos adentro: ";
		for (list<uint>::iterator it=p.adentro.begin(); it != p.adentro.end(); ++it)
			{
				o<< *it <<" "; 
			}
	    o<<endl;
	    o<<" Nodos que estan: ";
		for (uint i=0;i<p.esta.size();++i)
		{	if (p.esta[i])
				o<< i <<" ";
		}
	    o <<endl;
	    o << "Nodos candidatos: ";
		for (list<uint>::iterator it=p.candidato.begin(); it != p.candidato.end(); ++it)
			{
				o<< *it <<" "; 
			}	
		o<<endl;
		o<<"Cantidad de frontera: "<<p.cantFrontera<<endl;

	    return o;
	}


/* ----------------------------------------------------
	Quita el nodo "n" de la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu quitarNodo(uint n, const solucionTabu& solucion,const Grafo& g)
{
	if (!solucion.esta[n]) //control
		return solucion;
	solucionTabu salida = solucion;
	salida.esta[n] = false;
	salida.adentro.remove(n);
	//calculo nueva frontera
	int adentro = 0;
	if (salida.adentro.size() == 0) //si los candidatos antes eran todos ahora tengo que quedarme con los corrector (alcanza con hacer esto solo con el primer nodo de la lista)
	{
		salida.candidato.clear();
		for (uint i=0;i<g.nodos();++i)
		{ 
				salida.candidato.push_back(i);
		}
		salida.cantFrontera = 0;
	}else{
		for (list<uint>::iterator it=salida.adentro.begin(); it != salida.adentro.end() ; ++it)
		{
			if (g.sonVecinos(n,*it))
				++adentro; 
		}
	int afuera = g.vecindad(n).size() - adentro;
	salida.cantFrontera = salida.cantFrontera - afuera + adentro;
	}
	return salida; 
}

/* ----------------------------------------------------
	Agrega el nodo "n" a la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu agregarNodo(uint n, const solucionTabu& solucion,const Grafo& g){
	if (solucion.esta[n]) //de control
		{return solucion;}
	solucionTabu salida = solucion;
	
	if (solucion.candidato.size() == g.nodos()) //si los candidatos antes eran todos ahora tengo que quedarme con los corrector (alcanza con hacer esto solo con el primer nodo de la lista)
	{
		salida.candidato.clear();
		for (uint i=0;i<g.nodos();++i)
		{ 
			if (g.sonVecinos(i,n))
				salida.candidato.push_back(i);
		}
	}
	
	salida.esta[n] = true;
	salida.adentro.push_back(n);
	//calculo nueva frontera
	int adentro = 0;
	for (list<uint>::iterator it=salida.adentro.begin(); it != salida.adentro.end() ; ++it)
	{
		if (g.sonVecinos(n,*it))
			++adentro; 
	}
	int afuera = g.vecindad(n).size() - adentro;
	salida.cantFrontera = salida.cantFrontera - adentro + afuera;
	return salida;
}

/* --------------------------------------------------

	Calcula la cardinalidad de la frontera de g
	Complejidad:

----------------------------------------------------- */

uint cantFrontera(solucionTabu sol )
{
	return (sol.cantFrontera);
}


/* ---------------------------------------------------

	Calcula Mejor solucion agregando un nodo

-----------------------------------------------------*/

int mejorSolucionAgregando(solucionTabu& gt_0, solucionTabu& gt_inicial, const Grafo& g)
{
	int nodo = 0;
	int nod = *(gt_inicial.candidato.begin());	
	solucionTabu gt_mejor = agregarNodo(nod,gt_inicial,g);
	for (list<uint>::iterator it=gt_inicial.candidato.begin(); it != gt_inicial.candidato.end(); ++it)
	{
		if (!gt_inicial.esta[*it])
		{
			if (listabu[*it]==0) //no es tabu
			{		
				if (cantFrontera(gt_mejor) < cantFrontera( agregarNodo(*it,gt_inicial,g) ))
				{
					gt_mejor = agregarNodo(*it,gt_mejor,g);
					nodo = *it;
				}
			}else{
				if (listabu[*it]<maxValorTabu/2-1 && cantFrontera(gt_mejor) <= cantFrontera( agregarNodo(*it,gt_inicial,g) ))
				{
					gt_mejor = agregarNodo(*it,gt_mejor,g);
					nodo = *it;
				}
			}	
		}
	}
	gt_0 = gt_mejor;
	return nodo;
}

/* ---------------------------------------------------

	Calcula Mejor solucion quitando un nodo

-----------------------------------------------------*/

int mejorSolucionQuitando(solucionTabu& gt_0, solucionTabu gt_inicial,Grafo& g){
	int nodo = 0;
	solucionTabu gt_mejor = quitarNodo(*(gt_inicial.adentro.begin()),gt_inicial,g);

	for (list<uint>::iterator it=gt_inicial.adentro.begin(); it != gt_inicial.adentro.end(); ++it)
	{
		if ( listabu[*it] )
		{
			if (cantFrontera(gt_mejor) < cantFrontera( quitarNodo(*it,gt_inicial,g)))
			{
				gt_mejor = quitarNodo(*it,gt_inicial,g);
				nodo = *it;
			}
		}else{
			if (listabu[*it]<maxValorTabu/2-1 && cantFrontera(gt_mejor) <= cantFrontera( agregarNodo(*it,gt_inicial,g) ))
			{
				gt_mejor = quitarNodo(*it,gt_mejor,g);
				nodo = *it;
			}
		}
	}
	gt_0 = gt_mejor;
	return nodo;
}
/* ---------------------------------------------------

	Tabu Search

------------------------------------------------------ */

vector<uint> tabuSearch(vector<uint>& solIni, Grafo& g, uint desviacion_permitida)
{
	listabu.clear();
	maxValorTabu = 0;

	for(int i=0;i<g.nodos();++i)
		listabu.push_back(0);				
	solucionTabu gt_actual(g, solIni ); 	//solucion inicial, aca tengo que poner la LOCAL
	solucionTabu gt_mejor(g,solIni);   	//mejor solucion
	solucionTabu gt_0(g),gt_1(g);
	int nodo_0,nodo_1;
	bool mejora_frontera = true;
	while(mejora_frontera || desviacion_permitida>0) //paro cuando no mejora la solucion o no puedo descender mas
	{
		nodo_0 = mejorSolucionAgregando(gt_0,gt_actual,g); //modifica solo el primer parametro
		nodo_1 = mejorSolucionQuitando(gt_1,gt_actual,g); //modifica solo el primer parametro
		if (cantFrontera(gt_0) < cantFrontera(gt_1))
		{
			gt_0 = gt_1;
			nodo_0 = nodo_1;
		} 
		if (cantFrontera(gt_actual) < cantFrontera(gt_0)){
			gt_actual = gt_0;
			mejora_frontera = true;
		}else{
			mejora_frontera = false;
			desviacion_permitida--;
			//los pongo en la lista tabu
			maxValorTabu++;
			listabu[nodo_0] = maxValorTabu;
		}
		gt_actual = gt_0;
		if (cantFrontera(gt_mejor) < cantFrontera(gt_0)){
			gt_mejor = gt_0;
		}
	}

	return ( gt_mejor.toVec() );

}

/*---------------------------------------------------

MODULO DE TESTS

-------------------------------------------------*/

bool testSolucionTabu(vector<uint>& solIni,Grafo& g)
{
	bool val = true;
	solucionTabu gt_0(g);
	cout<<gt_0<<endl;
	solucionTabu gt_1(g, solIni);
 	val = val && !(gt_1 == gt_0); //anda igualdad
	gt_0 = gt_1;
	val = val && gt_0 == gt_1; //anda copia
	solucionTabu gt_2(g);
	val = val && !(gt_0 == gt_2);
	cout<<gt_0<<endl; //ver contenido
	val = val && (gt_0.cantFrontera == cantFrontera(gt_0)); //devuelve bien la frontera
	gt_1 = quitarNodo(2,gt_0, g); //quita bien el nodo
	cout<<gt_1<<endl;
	gt_1 = agregarNodo(2,gt_0, g); //agrega bien el nodo
	cout<<gt_1<<endl;
	return val;
}

bool calculoDeSoluciones(Grafo& g)
{
	vector<uint> solIni;
	solIni.push_back(1);
	solucionTabu gt_0(g, solIni);
	solucionTabu gt_actual = gt_0;
	int nodo_0;
	cout<<gt_actual<<endl;
	nodo_0 = mejorSolucionAgregando(gt_0,gt_actual,g);
	cout<<gt_0<<endl;
	return true;
}


void testFunctions(vector<uint>& solIni, Grafo& g, uint desviacion_permitida) //PARA EL PRIMER CASO DE LA CATEDRA
{
	//cout<< boolalpha <<testSolucionTabu(solIni,g)<<endl;
	cout<< boolalpha <<calculoDeSoluciones(g)<<endl;

}


/*-----------------------------------

HASTA ACA MODULO TEST
------------------------------------*/


int main() {

	uint desviacion_permitida = 30 ;	// cantidad de iteraciones maximas en las que va a disminuir

	int termino = '1';
	while (termino != '0') {
		uint n, m;
		cin >> n >> m;

		Grafo grafo(n);
		for (int i=0; i<m; i++) {  //O(n²)
			uint u,v;
			cin >> u >> v;
			u--; v--;

			grafo.agregarArista(u, v);
		}
	auto t1 = chrono::high_resolution_clock::now();
	vector<uint> solinicial,clique;
	solinicial.push_back(2);
	clique = tabuSearch(solinicial, grafo,desviacion_permitida);
	         //testFunctions(solinicial,grafo,desviacion_permitida);
	cout << grafo.frontera(clique) << " " << clique.size() << " ";
	for (int i = 0; i < clique.size(); i++) //O(n)
		cout << clique[i] + 1<< " ";
		
	cout << endl;
	
	auto t2 = chrono::high_resolution_clock::now();
	auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
	cerr << n << " " << m << " " << x << endl;
	
	termino = (cin >> ws).peek();
	}

	return 0;
}
