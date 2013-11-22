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


goloso=load("calidadGrande/goloso_2.dat");
local=load("calidadGrande/local_2.dat");
#tabu=load("calidadGrande/tabu_2.dat");

plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Rueda");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_rueda_calidad_solucion.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goloso=load("calidadGrande/goloso_3.dat");
local=load("calidadGrande/local_3.dat");
#tabu=load("calidadGrande/tabu_3.dat");


plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
#plot(goloso(:,1), goloso(:,1), '-r', 'LineWidth', 2,local(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Banana");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_banana_calidad_solucion.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goloso=load("calidadGrande/goloso_4.dat");
local=load("calidadGrande/local_4.dat");
#tabu=load("calidadGrande/tabu_4.dat");

plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
#plot(goloso(:,1), goloso_dat(:,1), '-r', 'LineWidth', 2,local(:,1), local_dat(:,1), '-g', 'LineWidth', 2,tabu(:,1), tabu_dat(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo completo");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_completo_calidad_solucion.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goloso=load("calidadGrande/goloso_14.dat");
local=load("calidadGrande/local_14.dat");
#tabu=load("calidadGrande/tabu_14.dat");

plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
#plot(goloso(:,1), goloso(:,1), '-r', 'LineWidth', 2,local(:,1), local(:,1), '-g', 'LineWidth', 2,tabu(:,1), tabu(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + Puente + CMF");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaPuenteCMF_calidad_solucion.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goloso=load("calidadGrande/goloso_15.dat");
local=load("calidadGrande/local_15.dat");
#tabu=load("calidadGrande/tabu_15.dat");

plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
#plot(goloso(:,1), goloso(:,1), '-r', 'LineWidth', 2,local(:,1), local(:,1), '-g', 'LineWidth', 2,tabu(:,1), tabu(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + CMF");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaCMF_calidad_solucion.jpg");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goloso=load("calidadGrande/goloso_17.dat");
local=load("calidadGrande/local_17.dat");
#tabu=load("calidadGrande/tabu_17.dat");

plot(goloso(:,2), goloso(:,1), '-r', 'LineWidth', 2,local(:,2), local(:,1), '-g', 'LineWidth', 2);
#plot(goloso(:,1), goloso(:,1), '-r', 'LineWidth', 2,local(:,1), local(:,1), '-g', 'LineWidth', 2,tabu(:,1), tabu(:,1), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Estrella + Puente + Doble Estrella");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_estrellaPuenteDobleEstrella_calidad_solucion.jpg");
