/*
4 158000
5 114000
6 109000
7 131000
8 247000
9 410000
10 477000
11 267000
12 390000
13 517000
14 685000
15 395000
16 777000
17 1031000
18 807000
19 1613000
20 1212000
25 3341000
30 4110000
35 6940000
40 11835000
45 14625000
50 23493000
55 28472000
60 30988000
65 39424000
70 49450000
75 50328000
80 57218000
85 71475000
90 94968000
95 136060000
100 122177000
105 203771000
110 213423000
115 241567000
120 324826000
125 355609000
100 54679296000
110 89575505000
120 227419387000
130 282154824000
140 569957251000
150 797604740000
160 1255373373000
170 1899427962000
180 3470524538000
190 5085067962000
*/


#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
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

int calcularFrontera(vector<int> nodos) { //ASUME QUE LO QUE ENTRA ES UNA CLIQUE
	int res=0;
	for (int i = 0; i < nodos.size(); ++i)
		res = res + (g[nodos[i]].size() - (nodos.size() - 1));
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

 	int fronteraActual = calcularFrontera(clique);

 	if (!candidatos.empty())
 		clique.resize(clique.size()+1);

 	while (!candidatos.empty()) {
 		clique[clique.size()-1] = candidatos.front(); candidatos.pop();
 		int fClique = calcularFrontera(clique);
 		if (fClique > maxCmf) {
 			maxCmf = fClique;
 			cmf = clique;
 		}
 		if (calcularFrontera(clique) > fronteraActual)
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

	cout << maxCmf << " " << cmf.size() << " ";
	for (int i = 0; i < cmf.size(); ++i)
		cout << cmf[i]+1 << " ";
	cout << endl;
}


int main() {

	int n, m;
	int termino = '1';
	while (termino != '0') {
		g.clear();
		maxCmf=-1;
		cmf.clear();
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
		cerr << maxCmf << " " << n << " " << x << endl;
		termino = (cin >> ws).peek();
	}



	return 0;
}
