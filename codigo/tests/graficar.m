# Ya estoy en la carpeta correcta


#### OBJETIVO:
# waitingTime[cantDeCores][valorDeQuantum] = media de las mediciones
# turnaroundTime[cantDeCores][valorDeQuantum] = media de las mediciones
# fairness[cantDeCores][valorDeQuantum][tareaNro] = media de las mediciones
# waitingTimePromedio[cantDeCores][valorDeQuantum][tareaNro] = media de las mediciones

#Levanto los outputs de los tests (que genero el parser):
#for cpu = [1:4]
#	for quantum = [1:length(valoresDeQuantum)]
#		datosAux = load(strcat("output/salida.cpu-",int2str(cpu),"-quantum-",int2str(valoresDeQuantum(quantum)),".out"));
#		
#		waitingTime(cpu,quantum) = mean(datosAux(:,1));
#		turnaroundTime(cpu,quantum) = mean(datosAux(:,2));
#		for nroTarea= [1:6]
#			fairness(cpu,quantum,nroTarea) = median(datosAux(:,2+nroTarea));
#			waitingTimePromedio(cpu,quantum,nroTarea) = median(datosAux(:,8+nroTarea));
#		endfor
#		fairnessVarianza(cpu,quantum) = var(fairness(cpu,quantum,:));
#	endfor
#endfor


# A graficar!

hold off;

#goloso=load("tiempos_goloso.dat");
#local=load("tiempos_local.dat");
tabu=load("tabu_complejidad_nodos.dat");
#subplot(1);

#plot(valoresDeQuantum,waitingTime(1,:), '-r', 'LineWidth', 2, valoresDeQuantum,waitingTime(2,:), '-g', 'LineWidth', 2, valoresDeQuantum,waitingTime(3,:), '-b', 'LineWidth', 2, valoresDeQuantum,waitingTime(4,:), '-c', 'LineWidth', 2);

plot(tabu(:,1), tabu(:,3), '-b', 'LineWidth', 2);
#plot(goloso(:,1), goloso(:,3), '-r', 'LineWidth', 2,local(:,1), local(:,3), '-g', 'LineWidth', 2,tabu(:,1), tabu(:,3), '-b', 'LineWidth', 2);
title("Comparacion heuristicas para grafos completos");
xlabel("Tamaño de la entrada");
ylabel("Tiempo de ejecución (ns)");
legend("Tabu");
#legend("Goloso","local","tabu");
#set(h,'Location','NorthEastOutside');
grid;
#%axis([0 600 0 1]);

#set(gca,'YTick',0:0.1:1);
#set(gca,'XTick',0:200:2000);


set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("prueba.jpg");
