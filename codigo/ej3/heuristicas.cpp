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

#include "header/greedysearch.h"
#include "header/localsearch.h"
#include "header/tabusearch.h"

int main()
{

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



	cout<<"Busqueda Golosa:"<<endl;
	auto t1 = chrono::high_resolution_clock::now();
	vector<uint> clique;

	clique = greedysearch(grafo);

	auto t2 = chrono::high_resolution_clock::now();
	auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
	cerr << n << " " << m << " " << x << endl;
	cout << grafo.frontera(clique) << " " << clique.size() << " ";
	for (int i = 0; i < clique.size(); i++) //O(n)
		cout << clique[i] + 1<< " ";
	cout << endl;



	cout<<"Busqueda Local:"<<endl;
	t1 = chrono::high_resolution_clock::now();

	vector<uint> solucion_inicial(1,0);
	clique = busquedaLocal(grafo,solucion_inicial,m);

	t2 = chrono::high_resolution_clock::now();
	x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
	cerr << n << " " << m << " " << x << endl;
	cout << grafo.frontera(clique) << " " << clique.size() << " ";
	for (int i = 0; i < clique.size(); i++) //O(n)
		cout << clique[i] + 1<< " ";
	cout << endl;



	cout<<"Busqueda TABU:"<<endl;
	

	vector<uint> solucion_inicial2(1,0);
	vector<uint> solinicial = busquedaLocal(grafo,solucion_inicial2,m);
	t1 = chrono::high_resolution_clock::now();
	uint desviacion_permitida = grafo.nodos()/2;	// cantidad de iteraciones maximas en las que va a disminuir
	clique = tabusearch(solinicial, grafo,desviacion_permitida);

	t2 = chrono::high_resolution_clock::now();
	x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
	cerr << n << " " << m << " " << x << endl;
	cout << grafo.frontera(clique) << " " << clique.size() << " ";
	for (int i = 0; i < clique.size(); i++) //O(n)
		cout << clique[i] + 1<< " ";
	cout << endl;
	
	termino = (cin >> ws).peek();
	}

	return 0;
}
