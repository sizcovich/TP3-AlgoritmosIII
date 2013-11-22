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

#include "header/localsearch.h"

typedef vector<uint> conjNodo;

vector<int> listabu;
int maxValorTabu;
unsigned int INF;


pair<conjNodo,uint> eliminarNodo(Grafo grafo, vector<uint> clique) { //quito el de menor grado 
	uint fronteraClique = grafo.frontera(clique);//O(n)
	
	if (clique.size()==0){
		return (make_pair(clique,INF));
	}
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
	
	pair <conjNodo,uint> res;
	res = make_pair (cliqueQuitando,minimoNodo);
	return res;	
}

pair<conjNodo,uint> insertarNodo(Grafo grafo, vector<uint> clique) { 
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
		
	//Empeoro o mejoro una vez el mejor caso, para usar Tabu
	if (posibleClique.size()>0){
	clique.push_back(posibleClique[0]);
	tamFrontera = grafo.frontera(clique); //O(n)
	clique.pop_back();
	maxFrontera = tamFrontera;
	nodo = posibleClique[0];}
	//hasta aca


	for (uint i = 0; i < posibleClique.size(); i++)	{ //busco al de mayor frontera //O(n²)
		clique.push_back(posibleClique[i]);
		tamFrontera = grafo.frontera(clique); //O(n)
		clique.pop_back();
		if (tamFrontera > maxFrontera) {
			maxFrontera = tamFrontera;
			nodo = posibleClique[i];
		}		
	}
	
	pair<conjNodo,uint> res;
	
	if (posibleClique.size() == 0)
		res = make_pair (clique,INF);
	else {
		clique.push_back(nodo);
		res = make_pair (clique,nodo);
		clique.pop_back();
	}
		
	return res;
}


pair<conjNodo,uint> mejorOperacion(Grafo g,conjNodo sol) //retorna la mejor solucion entre agregar,quitar o permutar un nodo, junto con el nodo con el cual realizo la misma
{
	uint nodo = 0;
	uint nodo_aux = 0;

	pair<conjNodo,uint> maximo = insertarNodo(g, sol); //O(n²)	
	pair<conjNodo,uint> aux = eliminarNodo(g, sol); //O(n)

	if ((g.frontera(aux.first) > g.frontera(maximo.first) && aux.second != INF) || maximo.second == INF)
		maximo = aux;

	return( maximo );
}


vector<uint> tabusearch(vector<uint>& solIni, Grafo& g, uint desviacion_permitida)
{
	listabu.clear();
	maxValorTabu = 0;
	int INF = g.nodos()+1;
	int cant_max_iter = g.nodos()*g.nodos();
	for(int i=0;i<g.nodos();++i)
		listabu.push_back(0);

	pair<conjNodo,uint> actual;
	actual.first = solIni;
	pair<conjNodo,uint> mejor;
	mejor.first = solIni; //"mejor" hasta ahora de los vecinos
	pair<conjNodo,uint> maxima;
	maxima.first = solIni;
	uint tamFrontera = g.frontera(solIni);
	bool mejora_frontera = true;
	int iter=0;
	while((mejora_frontera || 0 < desviacion_permitida) && iter<cant_max_iter) //paro cuando no mejora la solucion o no puedo descender mas
	{

		mejor = mejorOperacion(g,actual.first);

		if ( tamFrontera < g.frontera(mejor.first) ){
			mejora_frontera = true;
		}else{
			mejora_frontera = false;
			desviacion_permitida--;
			//los pongo en la lista tabu
			maxValorTabu++;
			listabu[mejor.second] = maxValorTabu;
		}
		tamFrontera = g.frontera(mejor.first);
		actual = mejor;
		if (g.frontera(maxima.first) < tamFrontera){
			maxima = mejor;
		}
		++iter;
	}
	return ( maxima.first );

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
		vector <uint> res;
		for (int i = 0; i < 10; ++i)
		{
			res.clear();
			res.push_back(0);
			int desviacion_permitida = grafo.nodos()/2;
			res = busquedaLocal(grafo, res, m);
			res = tabusearch(res,grafo,desviacion_permitida);
		}
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << grafo.frontera(res) << " " << n << " " << m << " " << (x/10) << endl;
		cout << grafo.frontera(res) << " " << res.size() << " ";
		for (int i = 0; i < res.size(); i++) //O(n)
			cout << res[i] + 1<< " ";
		cout << endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
