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

goloso_dat=load("goloso_12.dat");
local_dat=load("local_12.dat");
tabu_dat=load("tabu_12.dat");

plot(goloso_dat(:,2), goloso_dat(:,3), '-r', 'LineWidth', 2,local_dat(:,2), local_dat(:,3), '-g', 'LineWidth', 2,tabu_dat(:,2), tabu_dat(:,3), '-b', 'LineWidth', 2);
title("Comparación de calidad de soluciones para grafos tipo Rueda");
xlabel("Cantidad de nodos");
ylabel("Calidad de la solución");
legend("Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_rueda_performance_nodos_aristas.jpg");