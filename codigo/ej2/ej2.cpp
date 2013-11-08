#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <queue>
#include <ctgmath>
#include <iterator>

using namespace std; 

vector<vector<int> > g;
vector<int> cmf;
int maxCmf=-1;

void backtracking(vector<int> clique, queue<int> candidatos);
int calcularFrontera(vector<int> nodos);
void exacto();

int calcularFrontera(vector<int> nodos) {
	int res=0;
	sort(nodos.begin(), nodos.end());
	for (int i = 0; i < nodos.size(); ++i)
		for (int j = 0; j < g[nodos[i]].size(); ++j)
			if (!binary_search(nodos.begin(), nodos.end(), g[nodos[i]][j]))
				res++;
	return res;
}

queue<int> interseccionNAdyacentes(vector<int> indices) {

	vector<int> v_interseccion = g[indices[0]];
	vector<int> v_tmp;
	for (int i = 1; i < indices.size(); ++i) {
		set_intersection(v_interseccion.begin(), v_interseccion.end(),
							  g[indices[i]].begin(), g[indices[i]].end(),
							  back_inserter(v_tmp));
		v_interseccion = v_tmp;
		v_tmp.clear();
	}

	queue<int> res;
	for (int i = 0; i < v_interseccion.size(); ++i)
	{
		if (v_interseccion[i] > indices[indices.size()-1])
			res.push(v_interseccion[i]);
	}
	return res;
}

 void backtracking(vector<int> clique, queue<int> candidatos) {  //Asumo que el ultimo elemento del array es el ultimo elemento que agregue

 	if (!candidatos.empty())
 		clique.resize(clique.size()+1);

 	while (!candidatos.empty()) {
 		clique[clique.size()-1] = candidatos.front(); candidatos.pop();
 		int fClique = calcularFrontera(clique);
 		if (fClique > maxCmf) {
 			maxCmf = fClique;
 			cmf = clique;
 		}
 		backtracking(clique, interseccionNAdyacentes(clique));
 	}
 }

void exacto() {

	vector<int> clique;
	queue<int> candidatos;
	for (int i = 0; i < g.size(); ++i) {
		sort(g[i].begin(), g[i].end());
		candidatos.push(i);		
	}

	backtracking(clique, candidatos);

	// vector<int> prueba;
	// prueba.push_back(3);
	// prueba.push_back(0);
	// prueba.push_back(4);
	// prueba.push_back(7);
	// prueba.push_back(18);

	// cout << calcularFrontera(prueba) << endl;

	cout << maxCmf << endl;
	for (int i = 0; i < cmf.size(); ++i)
		cout << cmf[i]+1 << " ";
	cout << endl;
}


int main() {

	int n, m;
	int termino = '1';
	while (termino != '0') {
		g.clear();
		cin >> n;
		cin >> m;
		int v1, v2;

		g.resize(n);

		for (int i = 0; i < m; ++i) {
			cin >> v1;
			cin >> v2;
			g[v1-1].push_back(v2-1);
			g[v2-1].push_back(v1-1);
		}

		auto t1 = chrono::high_resolution_clock::now();
		exacto();
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << n+m << " " << x << endl;
		termino = (cin >> ws).peek();
	}



	return 0;
}
