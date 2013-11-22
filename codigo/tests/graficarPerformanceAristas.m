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

goloso_dat=load("performanceAristas/goloso_12_aristas.dat");
local_dat=load("performanceAristas/local_12_aristas.dat");
tabu_dat=load("performanceAristas/tabu_12_aristas.dat");

#plot(goloso_dat(:,3), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,3), local_dat(:,4), '-g', 'LineWidth', 2);
plot(goloso_dat(:,3), goloso_dat(:,4), '-r', 'LineWidth', 2,local_dat(:,3), local_dat(:,4), '-g', 'LineWidth', 2,tabu_dat(:,3), tabu_dat(:,4), '-b', 'LineWidth', 2);
title("Comparación de performance para grafos conexos por densidad");
xlabel("Cantidad de aristas");
ylabel("Tiempo de ejecución (ns)");
legend("Heuristica Golosa", "Heuristica Local", "Metaheuristica Tabu");
grid;

set(gcf,'PaperUnits','inches','PaperPosition',[0 0 8.5 5])

print("versus_performance_aristas.jpg");