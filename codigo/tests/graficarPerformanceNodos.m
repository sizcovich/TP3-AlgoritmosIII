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

goloso_dat=load("performance/goloso_4.dat");
local_dat=load("performance/local_4.dat");
tabu_dat=load("performance/tabu_4.dat");

#plot(goloso_dat(:,2), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,2), local_dat(:,4), '-g', 'LineWidth', 2);
plot(goloso_dat(:,2), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,2), local_dat(:,4), '-g', 'LineWidth', 2,tabu_dat(:,2), tabu_dat(:,4), '-b', 'LineWidth', 2);
title("Comparación de performance para grafos tipo completos");
xlabel("Cantidad de nodos");
ylabel("Tiempo de ejecución (ns)");
legend("Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_performance_nodos_completo.jpg");

goloso_dat=load("performance/goloso_12.dat");
local_dat=load("performance/local_12.dat");
tabu_dat=load("performance/tabu_12.dat");

#plot(goloso_dat(:,2), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,2), local_dat(:,4), '-g', 'LineWidth', 2);
plot(goloso_dat(:,2), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,2), local_dat(:,4), '-g', 'LineWidth', 2,tabu_dat(:,2), tabu_dat(:,4), '-b', 'LineWidth', 2);
title("Comparación de performance de soluciones para grafos conexos con densidad 50%");
xlabel("Cantidad de nodos");
ylabel("Tiempo de ejecución (ns)");
legend("Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_performance_nodos_conexo.jpg");
