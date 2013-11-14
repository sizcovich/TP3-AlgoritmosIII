g++ -std=c++0x heuristicaGolosa.cpp -o heuristicaGolosa

rm ./tiemposGoloso.dat
cd ..
for (( i = 4; i <= 20; i++ )); do
	#statements
	echo "test A1 - numero $i"
    
	cat ./ej2/tests/testA1/*.n_$i.in | ./ej3/heuristicaGolosa 1> /tmp/salida.tmp 2>> ./ej3/tiemposGoloso.dat
	diff --normal /tmp/salida.tmp ./ej2/tests/testA1/*.n_$i.out 

done

for (( i = 25; i <= 125; i=i+5 )); do
	#statements
	echo "test A2 - numero $i"
	cat ./ej2/tests/testA2/*.n_$i.in | ./ej3/heuristicaGolosa 1> /tmp/salida.tmp 2>> ./ej3/tiemposGoloso.dat
	diff --normal /tmp/salida.tmp ./ej2/tests/testA2/*.n_$i.out 

done

for (( i = 100; i <= 280; i=i+10 )); do
	#statements
	echo "test B - numero $i"
	cat ./ej2/tests/testB/*.n_$i.in | ./ej3/heuristicaGolosa 1> /tmp/salida.tmp 2>> ./ej3/tiemposGoloso.dat
	diff --normal /tmp/salida.tmp ./ej2/tests/testB/*.n_$i.in.out 

done
