#include<iostream>
#include<fstream>
#include<string>
#include<random_graphs_generators.hpp>

//OPCIONES
#define HOLE 0
#define STAR 1
#define WHEEL 2
#define BANANA 3
#define COMPLETE 4
#define BIPARTITE 5
#define BIPARTITE_DENSITY 6
#define BIPARTITE_CONNECTED 7
#define BIPARTITE_CONNECTED_DENSITY 8
#define BIPARTITE_COMPLETE 9
#define TREE 10
#define CONNECTED 11
#define CONNECTED_DENSITY 12
#define CONNECTED_DENSITY_RANGE 13
#define GREEDY_NOT_IN_CMF 14
#define GREEDY_IN_CMF 15
#define PLANAR 16
#define STAR_BRIDGE_DOUBLE_STAR 17

using namespace std;

uint from_how_many_nodes(uint choice){
    uint nodes;
    switch(choice){
        case HOLE:
            cout << "Cantidad de nodos de la instancia mas chica [min:3]: ";
            break;

        case BANANA:
            cout << "Cantidad de nodos de la instancia mas chica [min:3]: ";
            break;

        case GREEDY_NOT_IN_CMF:
            cout << "Cantidad de nodos de la instancia mas chica [min:16]: ";
            break;

        case GREEDY_IN_CMF:
            cout << "Cantidad de nodos de la instancia mas chica [min:17]: ";
            break;

        case PLANAR:
            cout << "Cantidad de nodos de la instancia mas chica [min:3]: ";
            break;

        case STAR_BRIDGE_DOUBLE_STAR:
            cout << "Cantidad de nodos de la instancia mas chica [min:15]: ";
            break;

        default:
            cout << "Cantidad de nodos de la instancia mas chica [min:2]: ";
            break;
    }
    cin >> nodes;

    return nodes;
}

uint to_how_many_nodes(uint min){
    uint nodes;
    cout << "Cantidad de nodos de la instancia mas grande [min:" << min << "]: ";
    cin >> nodes;

    return nodes;
}

float ask_density_range_low(){
    float density;
    cout << "Limite inferior de la densidad de ejes [min:0,max:0.99]: ";
    cin >> density;

    return density;
}

float ask_density_range_up(float low){
    float density;
    cout << "Limite superior de la densidad de ejes [min:" << low << ",max:1]: ";
    cin >> density;

    return density;
}

float ask_density(uint quant_nodes){
    float density;
    cout << "Densidad de ejes [min:0,max:1]: ";
    cin >> density;

    return density;
}

string ask_output_file(){
    string name;
    cout << "Nombre del archivo donde desea guardar la salida: ";
    cin >> name;

    return name;
}

uint ask_how_many_per_size(){
    uint quant;
    cout << "¿Cuantas instancias por tamano?: ";
    cin >> quant;

    return quant;
}

uint ask_increment(){
    uint inc;
    cout << "¿En cuanto desea incrementar el tamano de las instancias? [ej: 1,5,10]: ";
    cin >> inc;

    return inc;
}

int main(int argc,char* argv[]){
    //Variables locales
    uint choice,nodes_lower,nodes_upper,inc,quant_per_size;
    float density,density_upper;
    ofstream output_file;

    //Pedimos data al usuario
    // 0 cout << HOLE                        << ".  Agujero" << endl;
    // 1 cout << STAR                        << ".  Estrella" << endl;
    // 2 cout << WHEEL                       << ".  Rueda" << endl;
    // 3 cout << BANANA                      << ".  Banana Tree" << endl;
    // 4 cout << COMPLETE                    << ".  Completo" << endl;
    // 5 cout << BIPARTITE                   << ".  Bipartito" << endl;
    // 6 cout << BIPARTITE_DENSITY           << ".  Bipartito por densidad de ejes" << endl;
    // 7 cout << BIPARTITE_CONNECTED         << ".  Bipartito Conexo" << endl;
    // 8 cout << BIPARTITE_CONNECTED_DENSITY << ".  Bipartito Conexo por densidad de ejes" << endl;
    // 9 cout << BIPARTITE_COMPLETE          << ".  Bipartito Completo" << endl;
    // 10 cout << TREE                        << ". Arbol" << endl;
    // 11 cout << CONNECTED                   << ". Conexo" << endl;
    // 12 cout << CONNECTED_DENSITY           << ". Conexo por densidad de ejes" << endl;
    // 13 cout << CONNECTED_DENSITY_RANGE     << ". Conexo por rango de densidad de ejes" << endl;
    // 14 cout << GREEDY_NOT_IN_CMF           << ". Estrella+Puente+CMF" << endl;
    // 15 cout << GREEDY_IN_CMF               << ". Estrella+CMF" << endl;
    // 16 cout << PLANAR                      << ". Planar" << endl;
    // 17 cout << STAR_BRIDGE_DOUBLE_STAR     << ". Estrella+Puente+Doble Estrella" << endl;
    // 18 cout << "Seleccione una opcion: ";
    // cin >> choice;

    
    // nodes_lower = from_how_many_nodes(choice);
    // nodes_upper = to_how_many_nodes(nodes_lower);
    // output_file.open(ask_output_file().c_str(),std::ios::app);
    // quant_per_size = ask_how_many_per_size();
    // inc = ask_increment();


    choice = atoi(argv[1]);
    nodes_lower = atoi(argv[2]);
    nodes_upper = atoi(argv[3]);
    output_file.open(argv[4], std::ios::app);
    quant_per_size = atoi(argv[5]);
    inc = atoi(argv[6]);
    if (argc == 8) {
        density = atof(argv[7]);
        cout << density << endl;
    }
    if (argc == 9) {
        density_upper = atof(argv[8]);
    }

    switch(choice){
        case HOLE:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_hole_graph(output_file,nodes);
            break;

        case STAR:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_star_graph(output_file,nodes);
            break;

        case WHEEL:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_wheel_graph(output_file,nodes);
            break;

        case BANANA:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_banana_tree_graph(output_file,nodes);
            break;

        case COMPLETE:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_complete_graph(output_file,nodes);
            break;

        case BIPARTITE:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_bipartite_graph(output_file,nodes,false);
            break;

        case BIPARTITE_DENSITY:
            // density = ask_density(nodes_lower);
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_bipartite_graph(output_file,nodes,density,false);
            break;

        case BIPARTITE_CONNECTED:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_bipartite_graph(output_file,nodes,true);
            break;

        case BIPARTITE_CONNECTED_DENSITY:
            // density = ask_density(nodes_lower);
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_bipartite_graph(output_file,nodes,density,true);
            break;

        case BIPARTITE_COMPLETE:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_complete_bipartite_graph(output_file,nodes);
            break;

        case TREE:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_tree_graph(output_file,nodes);
            break;

        case CONNECTED:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_connected_graph(output_file,nodes);
            break;

        case CONNECTED_DENSITY:
            // density = ask_density(nodes_lower);
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_connected_graph(output_file,nodes,density);
            break;

        case CONNECTED_DENSITY_RANGE:
            // density = ask_density_range_low();
            // density_upper = ask_density_range_up(density);
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_connected_graph(output_file,nodes,density,density_upper);
            break;

        case GREEDY_NOT_IN_CMF:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    highest_degree_node_not_in_CMF(output_file,nodes);
            break;

        case GREEDY_IN_CMF:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    highest_degree_node_in_CMF(output_file,nodes);
            break;

        // case PLANAR:
        //     for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
        //         for(uint quant = 0; quant<quant_per_size;++quant)
        //             random_planar_graph(output_file,nodes);
        //     break;

        case STAR_BRIDGE_DOUBLE_STAR:
            for(uint nodes = nodes_lower; nodes<=nodes_upper;nodes+=inc)
                for(uint quant = 0; quant<quant_per_size;++quant)
                    random_star_bridge_double_star(output_file,nodes);
            break;

        default:
            cout << "Opcion no existente" << endl;
            break;
    }

    output_file << '0' << endl;
    output_file.close();
    return 0;
}
