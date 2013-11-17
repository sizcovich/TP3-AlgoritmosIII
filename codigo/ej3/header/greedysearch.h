bool esClique(Grafo grafo, vector<uint> clique){ //O(n²)
    for (uint i=0; i<clique.size(); ++i) { //O(n)
        for (uint j=0; j<clique.size(); ++j) { //O(n)
            if(i != j){
            	if(!grafo.sonVecinos(clique[i],clique[j])) return false; //O(1)
            }
    	}
    }
    return true;
}

vector<uint> greedysearch(Grafo grafo){ //O(n⁴)
    vector<uint> cliqueHastaAhora(1,grafo.nodoDeMayorGrado()); //O(1)
    uint fronteraHastaAhora = grafo.frontera(cliqueHastaAhora); //pongo el grado del nodo de mayor grado - O(n)
	for(uint i = 0; i<grafo.nodos();++i){ //O(n)
        cliqueHastaAhora.push_back(i); //inserto el nodo i - O(1)
        if(esClique(grafo, cliqueHastaAhora)){ //pregunto si con el elemento insertado forma una clique - O(n²)
			if(grafo.frontera(cliqueHastaAhora) > fronteraHastaAhora){ //me fijo si la frontera de la nueva clique es mayor que la de la clique sin i - O(n)
            	fronteraHastaAhora = grafo.frontera(cliqueHastaAhora); //me guardo la nueva frontera - O(n)
        	}else{
                cliqueHastaAhora.pop_back(); //O(1)
            }
        }else{
                cliqueHastaAhora.pop_back(); //O(1)
		}
	}
	return cliqueHastaAhora;
}

