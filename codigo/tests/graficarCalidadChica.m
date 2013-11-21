# Ya estoy en la carpeta correcta

# A graficar!

clear;
hold off;


# 2  	WHEEL							Rueda
# 3 	BANANA						  	Banana Tree
# 4  	COMPLETE						Completo
# 9  	BIPARTITE_COMPLETE				Bipartito Completo
# 12  	CONNECTED_DENSITY				Conexo por densidad de ejes
# 14  	GREEDY_NOT_IN_CMF				Estrella+Puente+CMF
# 15  	GREEDY_IN_CMF					Estrella+CMF
# 17  	STAR_BRIDGE_DOUBLE_STAR			Estrella+Puente+Doble Estrella

exacto_out=load("exacto_2.out");
exacto_dat=load("exacto_2.dat");
goloso_out=load("goloso_2.out");
goloso_dat=load("goloso_2.dat");
local_out=load("local_2.out");
local_dat=load("local_2.dat");
tabu_out=load("tabu_2.out");
tabu_dat=load("tabu_2.dat");

plot(exacto_out(:,1), exacto_dat(:,1), '-y', 'LineWidth', 2, goloso_out(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local_out(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu_out(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Rueda");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Algoritmo Exacto","Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_rueda_calidad_solucion_chica.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exacto_out=load("exacto_3.out");
exacto_dat=load("exacto_3.dat");
goloso_out=load("goloso_3.out");
goloso_dat=load("goloso_3.dat");
local_out=load("local_3.out");
local_dat=load("local_3.dat");
tabu_out=load("tabu_3.out");
tabu_dat=load("tabu_3.dat");

plot(exacto_out(:,1), exacto_dat(:,1), '-y', 'LineWidth', 2, goloso_out(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local_out(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu_out(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Banana");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Algoritmo Exacto","Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_banana_calidad_solucion_chica.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exacto_out=load("exacto_14.out");
exacto_dat=load("exacto_14.dat");
goloso_out=load("goloso_14.out");
goloso_dat=load("goloso_14.dat");
local_out=load("local_14.out");
local_dat=load("local_14.dat");
tabu_out=load("tabu_14.out");
tabu_dat=load("tabu_14.dat");

plot(exacto_out(:,1), exacto_dat(:,1), '-y', 'LineWidth', 2, goloso_out(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local_out(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu_out(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + Puente + CMF");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Algoritmo Exacto","Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaPuenteCMF_calidad_solucion_chica.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exacto_out=load("exacto_15.out");
exacto_dat=load("exacto_15.dat");
goloso_out=load("goloso_15.out");
goloso_dat=load("goloso_15.dat");
local_out=load("local_15.out");
local_dat=load("local_15.dat");
tabu_out=load("tabu_15.out");
tabu_dat=load("tabu_15.dat");

plot(exacto_out(:,1), exacto_dat(:,1), '-y', 'LineWidth', 2, goloso_out(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local_out(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu_out(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + CMF");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Algoritmo Exacto","Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaCMF_calidad_solucion_chica.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exacto_out=load("exacto_17.out");
exacto_dat=load("exacto_17.dat");
goloso_out=load("goloso_17.out");
goloso_dat=load("goloso_17.dat");
local_out=load("local_17.out");
local_dat=load("local_17.dat");
tabu_out=load("tabu_17.out");
tabu_dat=load("tabu_17.dat");

plot(exacto_out(:,1), exacto_dat(:,1), '-y', 'LineWidth', 2, goloso_out(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local_out(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu_out(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + Puente + Doble Estrella");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Algoritmo Exacto","Algoritmo Exacto","Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaPuenteDobleEstrella_calidad_solucion_chica.jpg");
