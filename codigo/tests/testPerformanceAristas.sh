make

#!/bin/bash

# TIPOS_DE_GRAFOS="2 3 4 9 14 15 17"
# GRAFOS_POR_DENSIDAD="6 12"
CANT_NODOS_FIJA_PARA_DENSIDAD=500 # Cantidad de nodos que van a tener los grafos donde variamos la cantidad de aristas
INPUT_FILE_GEN="/tmp/data.in" # Donde se guarda el .in (de donde se leen los datos para correr los programas)
QUANT_PER_SIZE=1 # Por cada numero de nodos que cantidad de instancias se hacen
INCREMENT=10 # De a cuanto se incrementa
# DENSITY="0.5"
# DENSITY_UP="1" 
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

echo "Corriendo todos los test..."
echo "Compilando..."
rm ../ej3/heuristicaGolosa
g++ -std=c++0x ../ej3/heuristicaGolosa.cpp -o ../ej3/heuristicaGolosa
rm ../ej3/heuristicaBusquedaLocal
g++ -std=c++0x ../ej3/heuristicaBusquedaLocal.cpp -o ../ej3/heuristicaBusquedaLocal
# rm ../ej3/busquedaTabu
# g++ -std=c++0x ../ej3/busquedaTabu.cpp -o ../ej3/busquedaTabu

for (( i = 10; i < 100; i=i+5 )); do	
	rm $INPUT_FILE_GEN
	echo "Creando grafos de tipo 12..."
	./graph_generator 12 $CANT_NODOS_FIJA_PARA_DENSIDAD $CANT_NODOS_FIJA_PARA_DENSIDAD $INPUT_FILE_GEN $QUANT_PER_SIZE 1 "0.$i"
	echo "Corriendo goloso.."
	cat $INPUT_FILE_GEN | $GOLOSO 1>> goloso_12.out 2>> goloso_12.dat
	echo "Corriendo local.."
	cat $INPUT_FILE_GEN | $LOCAL 1>> local_12.out 2>> local_12.dat
	# echo "Corriendo tabu.."
	# cat $INPUT_FILE_GEN | $TABU 1>> tabu_12.out 2>> tabu_12.dat
	echo "Listo!"
done

octave graficarPerformanceAristas.m