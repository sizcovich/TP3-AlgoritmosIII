g++ -std=c++0x ./ej2.cpp -o ./ej2
rm ./tiempos.dat

for (( i = 4; i <= 20; i++ )); do
	#statements
	echo "test A1 - numero $i"
	cat tests/testA1/*.n_$i.in | ./ej2 1> /tmp/salida.tmp 2>> ./tiempos.dat
	diff --normal /tmp/salida.tmp tests/testA1/*.n_$i.out 

done

for (( i = 25; i <= 125; i=i+5 )); do
	#statements
	echo "test A2 - numero $i"
	cat tests/testA2/*.n_$i.in | ./ej2 1> /tmp/salida.tmp 2>> ./tiempos.dat
	diff --normal /tmp/salida.tmp tests/testA2/*.n_$i.out 

done

for (( i = 100; i <= 280; i=i+10 )); do
	#statements
	echo "test B - numero $i"
	cat tests/testB/*.n_$i.in | ./ej2 1> /tmp/salida.tmp 2>> ./tiempos.dat
	diff --normal /tmp/salida.tmp tests/testB/*.n_$i.in.out 

done
