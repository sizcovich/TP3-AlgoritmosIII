TIPOS_DE_GRAFOS="2 3 14 15 17" # Identificadores de tipos de grafos que se van a hacer
CANT_NODOS_MIN=15 # CAntidad minima de nodos por cada grafo (MINIMO 15)
CANT_NODOS_MAX=105 # Cantidad maxima de nodos por cada grafo
INPUT_FILE_GEN="/tmp/data.in" # Donde se guarda el .in (de donde se leen los datos para correr los programas)
QUANT_PER_SIZE=1 # Por cada numero de nodos que cantidad de instancias se hacen
INCREMENT=10 # De a cuanto se incrementa
EXACTO="../ej2/ej2"
GOLOSO="../ej3/heuristicaGolosa"
LOCAL="../ej3/heuristicaBusquedaLocal"
TABU="../ej3/busquedaTabu"

# 2  	WHEEL							Rueda
# 3 	BANANA						  	Banana Tree
# 4  	COMPLETE						Completo
# 8  	BIPARTITE_CONNECTED_DENSITY		Bipartito Conexo por densidad de ejes
# 9  	BIPARTITE_COMPLETE				Bipartito Completo
# 12  	CONNECTED_DENSITY				Conexo por densidad de ejes
# 14  	GREEDY_NOT_IN_CMF				Estrella+Puente+CMF
# 15  	GREEDY_IN_CMF					Estrella+CMF
# 17  	STAR_BRIDGE_DOUBLE_STAR			Estrella+Puente+Doble Estrella


echo "Corriendo test de calidad de la solucion para grafos chicos: "
echo "Compilando..."
# rm ../ej2/ej2
# g++ -std=c++0x ../ej2/ej2.cpp -o ../ej2/ej2
rm ../ej3/heuristicaGolosa
g++ -std=c++0x ../ej3/heuristicaGolosa.cpp -o ../ej3/heuristicaGolosa
rm ../ej3/heuristicaBusquedaLocal
g++ -std=c++0x ../ej3/heuristicaBusquedaLocal.cpp -o ../ej3/heuristicaBusquedaLocal
rm ../ej3/busquedaTabu
g++ -std=c++0x ../ej3/busquedaTabu.cpp -o ../ej3/busquedaTabu

for i in $TIPOS_DE_GRAFOS; do
	echo "Creando grafos de tipo $i..."
	rm $INPUT_FILE_GEN
	./graph_generator $i $CANT_NODOS_MIN $CANT_NODOS_MAX $INPUT_FILE_GEN $QUANT_PER_SIZE $INCREMENT
	# echo "Corriendo exacto.."
	# cat $INPUT_FILE_GEN | $EXACTO 1>> /dev/null 2>> calidadChica/exacto_$i.dat
	# echo "Corriendo goloso.."
	# cat $INPUT_FILE_GEN | $GOLOSO 1>> /dev/null 2> calidadChica/goloso_$i.dat
	# echo "Corriendo local.."
	# cat $INPUT_FILE_GEN | $LOCAL 1>> /dev/null 2> calidadChica/local_$i.dat
	echo "Corriendo tabu.."
	cat $INPUT_FILE_GEN | $TABU 1>> tabu_$i.out 2>> tabu_$i.dat
	echo "Listo!"
done

# octave graficarCalidadChica.m
