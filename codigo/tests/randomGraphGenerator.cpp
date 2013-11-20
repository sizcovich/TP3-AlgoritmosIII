#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

void printEdges(vector<pair<int,int> > & v){
	for(unsigned int i = 0; i < v.size(); i++)
		cout << v[i].first << " " << v[i].second << endl;
	cout << endl;
}

int randomInRange(int lo, int hi){
	int delta = hi - lo + 1;
	int res = rand();
	res %= delta;
	res += delta;
	res %= delta;
	res += lo;
	return res;
}

bool Bernoulli(int num, int den){
	int x = randomInRange(0,den - 1);
	if(x < num)
		return true;
	else
		return false;
}

vector<pair<int,int> > edges_with_density(int n, int num, int den){///n vertices, densidad = num / den
	vector<pair<int,int> > res;

	for(int v = 1; v <= n; v++)
		for(int u = v + 1; u <= n; u++)
			if(Bernoulli(num,den))
				res.push_back(make_pair(v,u));

	return res;
}

void print_graphs_with_densities(int NUM_GRAPHS, int NUM_VERTICES, int num_g, int den_g, int num_h, int den_h){
	///imprime 'NUM_GRAPH' casos de prueba, en donde g y h tienen 'NUM_VERTICES'
	///vertices, y donde la probabilidad de un eje en g es 'num_g' / 'den_g'
	///y en h es 'num_h' / 'den_h'

	for(int graphs = 0; graphs < NUM_GRAPHS; graphs++){
		vector<pair<int,int> > eg = edges_with_density(NUM_VERTICES, num_g, den_g);
		vector<pair<int,int> > eh = edges_with_density(NUM_VERTICES, num_h, den_h);
		cout << NUM_VERTICES << " " << eg.size() << " " << eh.size() << endl;
		cout << endl;
		printEdges(eg);
		printEdges(eh);
	}

	cout << '#' << endl;
}

const char* nombre_programa;

void imprimirAyuda(){
	printf("AYUDA: este programa se ejecuta con siete parametros:\n\n");
	printf("- output_file_name: el nombre del archivo donde se desea escribir los tests generados.\n\n");
	printf("- num_grafos: la cantidad de grafos que desea que contenga el caso de prueba.\n\n");
	printf("- num_vertices: la cantidad de vertices que desea que contengan los grafos de los tests.\n\n");
	printf("- num_g: cada arista del grafo g se va a agregar con probabilidad num_g / den_g.\n\n");
	printf("- den_g: cada arista del grafo g se va a agregar con probabilidad num_g / den_g.\n\n");
	printf("- num_h: cada arista del grafo h se va a agregar con probabilidad num_h / den_h.\n\n");
	printf("- den_h: cada arista del grafo g se va a agregar con probabilidad num_h / den_h.\n\n");
	printf("Entonces, si por ejemplo queremos generar una familia de tests en el archivo \"myInput.txt\" que ");
	printf("consiste de 14 tests, cada uno con 11 vertices y en donde un arista esta en g con probabilidad ");
	printf("1 / 9 y un arista esta en h con probabilidad 2 / 5, escribimos: \n\n");
	printf("%s myInput.txt 14 11 1 9 2 5\n\n",nombre_programa);
	printf("le damos enter, y listo! :D\n\n");
}

int main(int argc, char** argv){
	nombre_programa = argv[0];

	FILE* f;

	if(argc == 1){
		f = freopen("input.txt","w",stdout);
		print_graphs_with_densities(10, 1000, 1, 2, 1, 2);
		fclose(f);
		exit(EXIT_SUCCESS);
	}

	if(argc != 8){
		imprimirAyuda();
		exit(EXIT_SUCCESS);
	}

	int string_index = 1;

	const char* output_file_name = argv[string_index++];
	const char* string_num_graphs = argv[string_index++];
	const char* string_num_vertices = argv[string_index++];
	const char* string_num_g = argv[string_index++];
	const char* string_den_g = argv[string_index++];
	const char* string_num_h = argv[string_index++];
	const char* string_den_h = argv[string_index++];

	int num_graphs = atoi(string_num_graphs);
	int num_vertices = atoi(string_num_vertices);
	int num_g = atoi(string_num_g);
	int den_g = atoi(string_den_g);
	int num_h = atoi(string_num_h);
	int den_h = atoi(string_den_h);

	f = freopen(output_file_name,"w",stdout);

	cerr << "Ejecutando programa generador de grafos aleatorios con parametros:" << endl;
	cerr << "output_file_name: " << output_file_name << endl;
	cerr << "num_graphs: " << num_graphs << endl;
	cerr << "num_vertices: " << num_vertices << endl;
	cerr << "num_g: " << num_g<< endl;
	cerr << "den_g: " << den_g << endl;
	cerr << "num_h: " << num_h << endl;
	cerr << "den_h: " << den_h << endl;
	cerr << endl;

	print_graphs_with_densities(num_graphs, num_vertices, num_g, den_g, num_h, den_h);

	cout << "Parametros de la familia de tests:" << endl;
	cout << "output_file_name: " << output_file_name << endl;
	cout << "num_graphs: " << num_graphs << endl;
	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_g: " << num_g<< endl;
	cout << "den_g: " << den_g << endl;
	cout << "num_h: " << num_h << endl;
	cout << "den_h: " << den_h << endl;

	fclose(f);

	return 0;
}
