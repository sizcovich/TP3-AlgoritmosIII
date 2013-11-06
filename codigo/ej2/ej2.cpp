#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <queue>
#include <ctgmath>

using namespace std; 


vector<vector<int> > g;
vector<int> cmf;
int maxCmf=-1;

bool esClique(vector<int> nodos);
int calcularFrontera(vector<int> nodos);
void exacto();

bool esClique(vector<int> nodos) {
	for (int i = 0; i < nodos.size(); ++i)
		for (int j = 0; j < nodos.size(); ++j)
			if (nodos[i]!=nodos[j] && !binary_search(g[nodos[i]].begin(), g[nodos[i]].end(), nodos[j]))
				return false;
	return true;
}

int calcularFrontera(vector<int> nodos) {
	int res=0;
	sort(nodos.begin(), nodos.end());
	for (int i = 0; i < nodos.size(); ++i)
		for (int j = 0; j < g[nodos[i]].size(); ++j)
			if (!binary_search(nodos.begin(), nodos.end(), g[nodos[i]][j]))
				res++;
	return res;
}



void exacto() {

	for (int i = 0; i < g.size(); ++i)
		sort(g[i].begin(), g[i].end());

	bool existeClique = true;
	int tamClique=2;
	vector<int> nodosDeClique;
	while (existeClique) {
		
	}

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
		cerr << cantTrabajos << " " << x << endl;
		termino = (cin >> ws).peek();
	}



	return 0;
}
