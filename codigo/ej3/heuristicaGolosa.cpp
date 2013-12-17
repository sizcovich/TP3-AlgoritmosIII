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

#include "header/greedysearch.h"


int main() {
	vector<uint> clique;
	int termino = '1';
	while (termino != '0') {
		uint n, m;
		cin >> n >> m;

		Grafo grafo(n); //O(n²)
		for (uint k=0; k<m; k++) {  //O(n²)
			uint i,j;
			cin >> i >> j;
			i--; j--;

			grafo.agregarArista(i, j);
		}
		
		auto t1 = chrono::high_resolution_clock::now();
		auto t2 = t1;
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

		const int CANT_ITERACIONES = 10;

		for (int i = 0; i < CANT_ITERACIONES; ++i)
		{
			clique = greedysearch(grafo);
			t2 = chrono::high_resolution_clock::now();
			x += chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		}

		
		cout << grafo.frontera(clique) << " " << clique.size() << " ";
		for (uint i = 0; i < clique.size(); i++) //O(n)
			cout << clique[i] + 1<< " ";	
		cout << endl;

		cerr << grafo.frontera(clique) << " " << n << " " << m << " " << (x/CANT_ITERACIONES) << endl;
		
		termino = (cin >> ws).peek();
	}
		
	return 0;
}
