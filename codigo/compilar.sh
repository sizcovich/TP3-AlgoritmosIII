#!/bin/sh

 g++ -std=c++0x -o ./ej3/heuristicaGolosa.exe ./ej3/heuristicaGolosa.cpp -lrt
 g++ -std=c++0x -o ./ej3/heuristicaBusquedaLocal.exe ./ej3/heuristicaBusquedaLocal.cpp -lrt
 g++ -std=c++0x -o  ./ej3/busquedaTabu.exe ./ej3/busquedaTabu.cpp -lrt
  # g++ -std=c++0x -o  ./ej3/heuristicas.exe ./ej3/heuristicas.cpp -lrt

 cat ./ej3/ej3.in | ./ej3/heuristicaGolosa.exe #1> ./ej3/heuristicaGolosa.out 2> ./ej3/heuristicaGolosa.dat
 cat ./ej3/ej3.in | ./ej3/heuristicaBusquedaLocal.exe # 1> ./ej3/heuristicaLocal.out 2> ./ej3/heuristicaLocal.dat
 cat ./ej3/ej3.in | ./ej3/busquedaTabu.exe # 1> ./ej3/heuristicaTabu.out 2> ./ej3/heuristicaTabu.dat
  # cat ./ej3/ej3.in | ./ej3/heuristicas.exe
