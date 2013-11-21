make

#!/bin/bash

# TIPOS_DE_GRAFOS="2 3 4 9 14 15 17"
# GRAFOS_POR_DENSIDAD="6 12"
TIPOS_DE_GRAFOS="2 3 4 9 14 15 17" # Identificadores de tipos de grafos que se van a hacer
GRAFOS_POR_DENSIDAD="12" # Identificados de tipos de grafos para variar la cantidad de aristas
CANT_NODOS_FIJA_PARA_DENSIDAD=1000 # Cantidad de nodos que van a tener los grafos donde variamos la cantidad de aristas
CANT_NODOS_MIN=15 # CAntidad minima de nodos por cada grafo (MINIMO 15)
CANT_NODOS_MAX=4000 # Cantidad maxima de nodos por cada grafo
INPUT_FILE_GEN="/tmp/data.in" # Donde se guarda el .in (de donde se leen los datos para correr los programas)
QUANT_PER_SIZE=1 # Por cada numero de nodos que cantidad de instancias se hacen
INCREMENT=10 # De a cuanto se incrementa
# DENSITY="0.5"
# DENSITY_UP="1" 
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


function exacto {
	rm ../ej2/ej2
	g++ -std=c++0x ../ej2/ej2.cpp -o ../ej2/ej2
	../ej2/ej2.sh
}
function goloso {
	echo "Corriendo test goloso..."
	rm ../ej3/heuristicaGolosa
	g++ -std=c++0x ../ej3/heuristicaGolosa.cpp -o $GOLOSO
	for i in $TIPOS_DE_GRAFOS; do
		echo "Creando grafos de tipo $i..."
		rm $INPUT_FILE_GEN
		./graph_generator $i $CANT_NODOS_MIN $CANT_NODOS_MAX $INPUT_FILE_GEN $QUANT_PER_SIZE $INCREMENT $DENSITY
		echo "Corriendo heuristica..."
		cat $INPUT_FILE_GEN | $GOLOSO 1>> goloso_$i.out 2>> goloso_$i.dat

		echo "Listo!.."
	done
	for g in $GRAFOS_POR_DENSIDAD; do
		echo "Tipo de grafo $g..."
		for (( i = 10; i < 100; i=i+5 )); do	
			rm $INPUT_FILE_GEN
			echo "Creando grafos de tipo $g..."
			./graph_generator $g $CANT_NODOS_FIJA_PARA_DENSIDAD $CANT_NODOS_FIJA_PARA_DENSIDAD $INPUT_FILE_GEN $QUANT_PER_SIZE 1 "0.$i"
			echo "Corriendo heuristica..."
			cat $INPUT_FILE_GEN | $GOLOSO 1>> goloso_$g.out 2>> goloso_$g.dat
			echo "Listo!.."
		done
	done
}
function local {
	echo "Corriendo test local..."
	rm ../ej3/heuristicaBusquedaLocal
	g++ -std=c++0x ../ej3/heuristicaBusquedaLocal.cpp -o $LOCAL
	for i in $TIPOS_DE_GRAFOS; do
		rm $INPUT_FILE_GEN
		echo "Creando grafos de tipo $i..."
		./graph_generator $i $CANT_NODOS_MIN $CANT_NODOS_MAX $INPUT_FILE_GEN $QUANT_PER_SIZE $INCREMENT $DENSITY
		echo "Corriendo heuristica..."
		cat $INPUT_FILE_GEN | $LOCAL 1>> local_$i.out 2>> local_$i.dat
		echo "Listo!.."
	done
	for g in $GRAFOS_POR_DENSIDAD; do
		echo "Tipo de grafo $g..."
		for (( i = 10; i < 100; i=i+5 )); do	
			rm $INPUT_FILE_GEN
			echo "Creando grafos de tipo $g..."
			./graph_generator $g $CANT_NODOS_FIJA_PARA_DENSIDAD $CANT_NODOS_FIJA_PARA_DENSIDAD $INPUT_FILE_GEN $QUANT_PER_SIZE 1 "0.$i"
			echo "Corriendo heuristica..."
			cat $INPUT_FILE_GEN | $LOCAL 1>> local_$g.out 2>> local_$g.dat
			echo "Listo!.."
		done
	done
}
function tabu {
	echo "Corriendo test tabu..."
	rm ../ej3/busquedaTabu
	g++ -std=c++0x ../ej3/busquedaTabu.cpp -o $TABU
	for i in $TIPOS_DE_GRAFOS; do
		rm $INPUT_FILE_GEN
		echo "Creando grafos de tipo $i..."
		./graph_generator $i $CANT_NODOS_MIN $CANT_NODOS_MAX $INPUT_FILE_GEN $QUANT_PER_SIZE $INCREMENT $DENSITY
		echo "Corriendo heuristica..."
		cat $INPUT_FILE_GEN | $TABU 1>> tabu_$i.out 2>> tabu_$i.dat
		echo "Listo!.."
	done
	for g in $GRAFOS_POR_DENSIDAD; do
		for (( i = 10; i < 100; i=i+5 )); do	
			rm $INPUT_FILE_GEN
			echo "Creando grafos de tipo $g..."
			./graph_generator $g $CANT_NODOS_FIJA_PARA_DENSIDAD $CANT_NODOS_FIJA_PARA_DENSIDAD $INPUT_FILE_GEN $QUANT_PER_SIZE 1 "0.$i"
			echo "Corriendo metaheuristica..."
			cat $INPUT_FILE_GEN | $TABU 1>> tabu_$g.out 2>> tabu_$g.dat
			echo "Listo!.."
		done
	done
}
function todo {
	echo "Corriendo todos los test..."
	echo "Compilando..."
	rm ../ej2/ej2
	g++ -std=c++0x ../ej2/ej2.cpp -o ../ej2/ej2
	rm ../ej3/heuristicaGolosa
	g++ -std=c++0x ../ej3/heuristicaGolosa.cpp -o ../ej3/heuristicaGolosa
	rm ../ej3/heuristicaBusquedaLocal
	g++ -std=c++0x ../ej3/heuristicaBusquedaLocal.cpp -o ../ej3/heuristicaBusquedaLocal
	rm ../ej3/busquedaTabu
	g++ -std=c++0x ../ej3/busquedaTabu.cpp -o ../ej3/busquedaTabu
	for i in $TIPOS_DE_GRAFOS; do
		rm $INPUT_FILE_GEN
		echo "Creando grafos de tipo $i..."
		./graph_generator $i $CANT_NODOS_MIN $CANT_NODOS_MAX $INPUT_FILE_GEN $QUANT_PER_SIZE $INCREMENT $DENSITY
		echo "Corriendo goloso.."
		cat $INPUT_FILE_GEN | $GOLOSO 1>> goloso_$i.out 2>> goloso_$i.dat
		echo "Corriendo local.."
		cat $INPUT_FILE_GEN | $LOCAL 1>> local_$i.out 2>> local_$i.dat
		echo "Corriendo tabu.."
		cat $INPUT_FILE_GEN | $TABU 1>> tabu_$i.out 2>> tabu_$i.dat
		echo "Listo!"
	done
	for g in $GRAFOS_POR_DENSIDAD; do
		for (( i = 10; i < 100; i=i+5 )); do	
			rm $INPUT_FILE_GEN
			echo "Creando grafos de tipo $g..."
			./graph_generator $g $CANT_NODOS_FIJA_PARA_DENSIDAD $CANT_NODOS_FIJA_PARA_DENSIDAD $INPUT_FILE_GEN $QUANT_PER_SIZE 1 "0.$i"
			echo "Corriendo goloso.."
			cat $INPUT_FILE_GEN | $GOLOSO 1>> goloso_$g.out 2>> goloso_$g.dat
			echo "Corriendo local.."
			cat $INPUT_FILE_GEN | $LOCAL 1>> local_$g.out 2>> local_$g.dat
			echo "Corriendo tabu.."
			cat $INPUT_FILE_GEN | $TABU 1>> tabu_$g.out 2>> tabu_$g.dat
			echo "Listo!"
		done
	done
}


clear
PS3='Que heuristica vas a testear?: '
OPTIONS="Exacto Goloso Local Tabu Todas"
select opt in $OPTIONS; do
	if [ "$opt" = "Exacto" ]; then
		exacto
		exit
	elif [ "$opt" = "Goloso" ]; then
		goloso
		exit
	elif [ "$opt" = "Local" ]; then
		local
		exit
	elif [ "$opt" = "Tabu" ]; then
		tabu
		exit
	elif [ "$opt" = "Todas" ]; then
		todo
		exit
	else
		clear
		echo mala opcion
	fi
done





















