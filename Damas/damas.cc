#include "Tablero.h"

int la_respuesta[tam][tam];

class minmax
{
public:
	Tablero* m_root;	
	int m_lvl_max;
	bool m_turno;
	minmax(int matriz[tam][tam],bool turno,int lvl)
	{
		m_root=new Tablero(turno);
		equals_matrices(m_root->tabl,matriz);
		m_lvl_max=lvl;
		m_turno = turno;
	}

	void contruir_arbol()
	{
		vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles_aux;//Vector Supremo segundo
		vector<Tablero* >jugadas;
		Tablero* aux;
		jugadas.push_back(m_root);
		int cont=0;
		while(jugadas.size()>0)
		{
			aux=jugadas[0];
			if(aux->m_lvl==m_lvl_max)break;
			jugadas.erase(jugadas.begin());
			aux->turno=(aux->turno+1)%2;
			aux->jugadas_permitidas();
			jugadas_posibles_aux=aux->jugadas_posibles;
			for(int i=0;i<jugadas_posibles_aux.size();i++)
			{
				for(int j=0;j<jugadas_posibles_aux[i].second.size();j++)
				{
					aux->m_child.push_back(new Tablero(m_turno,aux->tabl,aux->m_lvl));
					aux->m_child[aux->m_child.size()-1]->siguiente_jugada(aux->jugadas_posibles[i].first.first,aux->jugadas_posibles[i].first.second,aux->jugadas_posibles[i].second[j].first,aux->jugadas_posibles[i].second[j].second);
					jugadas.push_back(aux->m_child[aux->m_child.size()-1]);
				}
			}
			m_turno=(m_turno+1)%2;
			//cout<<aux->m_lvl<<endl;
		}
	}


};

int main()
{
	/*Tablero a(1);
	//cout<<a.tab[0][-1]<<endl;
	print_tablero(a.tabl);
	cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();
	print_tablero(a.tabl);
	cout<<"-----------------------------"<<endl;
	cout<<"posibles jugadas"<<endl;
	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		cout<<"posicion: "<<a.jugadas_posibles[i].first.first<<", "<<a.jugadas_posibles[i].first.second<<endl;
	}

	int tab[tam][tam];
	equals_matrices(tab,a.tabl);
	a.puede_comer(7,1,tab);
	cout<<"-------------------------------------------"<<endl;
	print_tablero(tab);
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;
	cout<<"TAMAÑO DE JGUADAS POSIBLES:>::>:>::>:>"<<a.jugadas_posibles.size()<<endl;

	for(int i=0;i<a.jugadas_posibles.size();i++)
	{
		cout<<"para el elemento "<<a.jugadas_posibles[i].first.first<<", "<<a.jugadas_posibles[i].first.second<<" sus jugadas posbiles son: ";
		for(int j=0;j<a.jugadas_posibles[i].second.size();j++)
		{
			cout<<"("<<a.jugadas_posibles[i].second[j].first<<", "<<a.jugadas_posibles[i].second[j].second<<"); ";
		}
		cout<<endl;
	}*/
	Tablero a(1);				///con 1 mueven las negras(1er jugador) y con 2 mueven las rojas.
	print_tablero(a.tabl);
	int i,j,i1,j1;
	cout<<"humano... selecciona la ficha que quieres mover.."<<endl;
	cin>>i;cin>>j;
	//falta si es que puede comer--preguntar
	cout<<"humano... selecciona la posicion a la que deseas mover la ficha seleccionada.."<<endl;
	cin>>i1;cin>>j1;
	a.siguiente_jugada(i,j,i1,j1);
	print_tablero(a.tabl);
	cin>>i1;
	cout<<endl;
	minmax b(a.tabl,0,4);
	b.contruir_arbol();
	print_tablero(b.m_root->m_child[1]->tabl);
	cout<<endl;
	print_tablero(b.m_root->m_child[1]->m_child[0]->tabl);
	cout<<endl;
	print_tablero(b.m_root->m_child[1]->m_child[0]->m_child[0]->tabl);

	return 0;
}

///falta min_max y borrar un 2 molesto...