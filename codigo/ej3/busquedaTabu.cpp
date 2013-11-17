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


#include "header/tabusearch.h"

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
	clique = tabusearch(solinicial, grafo,desviacion_permitida);
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
