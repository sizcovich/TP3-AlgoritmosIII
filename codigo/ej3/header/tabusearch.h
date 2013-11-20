//lista tabu: restringe nodos
vector<int> listabu;
int maxValorTabu;
unsigned int INF;

class solucionTabu
{
public:
	vector<bool> esta; // pone 1 en la iesima posicion si el nodo se encuentra y 0 en otro caso.
	list<uint> adentro; //contiene los nodos pertenecientes a la solucion
	list<uint> candidato; //contiene los nodos candidatos a formar una clique con la solucion inicial. CANDIDATOS A AGREGAR
	uint cantFrontera; //tiene el tamaño de la frontera para la solucion actual

	solucionTabu(Grafo& g)
	{
		cantFrontera = 0;
		//inicializo el estado de los nodos	
		for (int i=0;i<g.nodos();++i){
			esta.push_back(false);
			candidato.push_back(i);}
		
	}

	solucionTabu(Grafo& g, vector<uint>& solInicial)
	{
		cantFrontera = 0;
		//inicializo el estado de los nodos	
		for (int i=0;i<g.nodos();++i)
			esta.push_back(false);
		// guardo adentro la solucion inicial
		for (int i=0;i<solInicial.size();++i){
			adentro.push_back(solInicial[i]);
		}
		
		for (vector<uint>::iterator it=solInicial.begin(); it != solInicial.end(); ++it)
		{
			//actualizo estados
			esta[ *it ] = true; 
			//guardo grados de nodos
			cantFrontera += g.vecindad( *it ).size();
			for (vector<uint>::iterator it2=solInicial.begin(); it2 != solInicial.end(); ++it2)
			{		
				if (g.sonVecinos(*it,*it2) && *it != *it2)
					--cantFrontera;
			}
		}
		for (uint i=0;i<g.nodos();++i)
		{
			bool estaEnClique = true;
			for (list<uint>::iterator it=adentro.begin(); it != adentro.end()  && estaEnClique; ++it)
			{
				estaEnClique &= g.sonVecinos(i,*it); 
			}
			if (estaEnClique)
				candidato.push_back(i);
		}
		
	}

	vector<uint> toVec()
	{
		vector<uint> salida{ make_move_iterator( begin(adentro) ), make_move_iterator( end(adentro) ) };
		return (salida);
	}

	bool operator ==(const solucionTabu &p2)
	{
		return(this->esta == p2.esta && this->adentro==p2.adentro && this->candidato==p2.candidato && this->cantFrontera==p2.cantFrontera);
	}


};

	ostream& operator << (ostream &o,solucionTabu &p)
	{
	    o << "Nodos adentro: ";
		for (list<uint>::iterator it=p.adentro.begin(); it != p.adentro.end(); ++it)
			{
				o<< *it <<" "; 
			}
	    o<<endl;
	    o<<" Nodos que estan: ";
		for (uint i=0;i<p.esta.size();++i)
		{	if (p.esta[i])
				o<< i <<" ";
		}
	    o <<endl;
	    o << "Nodos candidatos: ";
		for (list<uint>::iterator it=p.candidato.begin(); it != p.candidato.end(); ++it)
			{
				o<< *it <<" "; 
			}	
		o<<endl;
		o<<"Cantidad de frontera: "<<p.cantFrontera<<endl;

	    return o;
	}


/* ----------------------------------------------------
	Quita el nodo "n" de la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu quitarNodo(uint n, const solucionTabu& solucion,const Grafo& g)
{
	if (!solucion.esta[n]) //control
		return solucion;
	solucionTabu salida = solucion;
	salida.esta[n] = false;
	salida.adentro.remove(n);
	//calculo nueva frontera
	if (salida.adentro.size() == 0) //si los candidatos antes eran todos ahora tengo que quedarme con los corrector (alcanza con hacer esto solo con el primer nodo de la lista)
	{
		salida.candidato.clear();
		for (uint i=0;i<g.nodos();++i)
		{ 
				salida.candidato.push_back(i);
		}
		salida.cantFrontera = 0;
	}else{
		salida.candidato.push_back(n); //despues de sacarlo se convierte en candidato
		int ady_adentro = 0;
		for (list<uint>::iterator it=salida.adentro.begin(); it != salida.adentro.end() ; ++it)
		{
			if (g.sonVecinos(n,*it))
				++ady_adentro; 
		}
	int ady_afuera = g.vecindad(n).size() - ady_adentro;
	salida.cantFrontera = salida.cantFrontera - ady_afuera + ady_adentro;
	}
	return salida; 
}

/* ----------------------------------------------------
	Agrega el nodo "n" a la solucion.
	Complejidad:
------------------------------------------------------- */
solucionTabu agregarNodo(uint n, const solucionTabu& solucion,const Grafo& g){
	if (solucion.esta[n]) //de control
		{return solucion;}

	solucionTabu salida = solucion;
	salida.esta[n] = true;
	salida.adentro.push_back(n);	
	if (solucion.candidato.size() == g.nodos()) //Es el caso en el que agrego un nodo por primera vez
	{
		salida.candidato.clear();
		for (uint i=0;i<g.vecindad(n).size();++i)
		{ 
			salida.candidato.push_back( g.vecindad(n)[i] );
		}
		salida.cantFrontera = g.vecindad(n).size();
	}else{
	salida.candidato.remove(n);
	//calculo nueva frontera
	int adentro = 0;
	for (list<uint>::iterator it=salida.adentro.begin(); it != salida.adentro.end() ; ++it)
	{
		if (g.sonVecinos(n,*it))
			++adentro; 
	}
	int afuera = g.vecindad(n).size() - adentro;
	salida.cantFrontera = salida.cantFrontera - adentro + afuera;
	}
	return salida;
}

/* --------------------------------------------------

	Calcula la cardinalidad de la frontera de g
	Complejidad:

----------------------------------------------------- */

uint cantFrontera(solucionTabu sol )
{
	return (sol.cantFrontera);
}


/* ---------------------------------------------------

	Calcula Mejor solucion agregando un nodo

-----------------------------------------------------*/

int mejorSolucionAgregando(solucionTabu& gt_0, const solucionTabu& gt_inicial, const Grafo& g)
{
	int nodo = INF;
	if (gt_inicial.candidato.size() != 0) //si no hay candidatos para agregar
	{	
		solucionTabu gt_mejor = agregarNodo(*(gt_inicial.candidato.begin()),gt_inicial,g);
		for (list<uint>::const_iterator it=gt_inicial.candidato.begin(); it != gt_inicial.candidato.end(); ++it)
		{
			if (listabu[*it]==0) //no es tabu
			{		
					if (cantFrontera(gt_mejor) < cantFrontera( agregarNodo(*it,gt_inicial,g) ))
					{
						gt_mejor = agregarNodo(*it,gt_mejor,g);
						nodo = *it;
					}
			}else{
				if (listabu[*it]<maxValorTabu/2-1 && cantFrontera(gt_mejor) <= cantFrontera( agregarNodo(*it,gt_inicial,g) ))
				{
						gt_mejor = agregarNodo(*it,gt_mejor,g);
						nodo = *it;
				}
			}	
		}
		gt_0 = gt_mejor;
	}
	return nodo;
}

/* ---------------------------------------------------

	Calcula Mejor solucion quitando un nodo

-----------------------------------------------------*/

int mejorSolucionQuitando(solucionTabu& gt_0, const solucionTabu gt_inicial,Grafo& g){
	int nodo = INF;
	if (gt_inicial.adentro.size() != 0) //si no hay candidatos para quitar
	{
		solucionTabu gt_mejor = quitarNodo(*(gt_inicial.adentro.begin()),gt_inicial,g);

		for (list<uint>::const_iterator it=gt_inicial.adentro.begin(); it != gt_inicial.adentro.end(); ++it)
		{
			if ( listabu[*it] )
			{
				if (cantFrontera(gt_mejor) < cantFrontera( quitarNodo(*it,gt_inicial,g)))
				{
					gt_mejor = quitarNodo(*it,gt_inicial,g);
					nodo = *it;
				}
			}else{
				if (listabu[*it]<maxValorTabu/2-1 && cantFrontera(gt_mejor) <= cantFrontera( agregarNodo(*it,gt_inicial,g) ))
				{
					gt_mejor = quitarNodo(*it,gt_mejor,g);
					nodo = *it;
				}
			}
		}
		gt_0 = gt_mejor;
	}
	return nodo;
}
/* ---------------------------------------------------

	Tabu Search

------------------------------------------------------ */

vector<uint> tabusearch(vector<uint>& solIni, Grafo& g, uint desviacion_permitida)
{
	listabu.clear();
	INF = g.nodos() + 1;
	maxValorTabu = 0;

	for(int i=0;i<g.nodos();++i)
		listabu.push_back(0);				
	solucionTabu gt_actual(g, solIni ); 	//solucion inicial
	solucionTabu gt_mejor(g,solIni);   	//mejor solucion
	solucionTabu gt_0(g),gt_1(g);
	int nodo_0,nodo_1;
	bool mejora_frontera = true;
	while(mejora_frontera || desviacion_permitida>0) //paro cuando no mejora la solucion o no puedo descender mas
	{
		nodo_0 = mejorSolucionAgregando(gt_0,gt_actual,g); //modifica solo el primer parametro
		nodo_1 = mejorSolucionQuitando(gt_1,gt_actual,g); //modifica solo el primer parametro
		if ((cantFrontera(gt_0) < cantFrontera(gt_1) && nodo_0 != INF) || (nodo_1 == INF))
		{
			gt_0 = gt_1;
			nodo_0 = nodo_1;
		} 
		if (cantFrontera(gt_actual) < cantFrontera(gt_0)){
			mejora_frontera = true;
		}else{
			mejora_frontera = false;
			desviacion_permitida--;
			//los pongo en la lista tabu
			maxValorTabu++;
			listabu[nodo_0] = maxValorTabu;
		}
		gt_actual = gt_0;
		if (cantFrontera(gt_mejor) < cantFrontera(gt_actual)){
			gt_mejor = gt_actual;
		}
	}

	return ( gt_mejor.toVec() );

}
