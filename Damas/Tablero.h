#include "funciones.h"

class Tablero
{
public:
	int tabl[tam][tam];
	bool turno;				//1 es turno del primero, 0 del segndo
    int fichas_negras,fichas_rojas;
    int m_lvl;
    vector<Tablero*>m_child;
	vector< pair< pair<int,int>, vector< pair<int,int> > > >jugadas_posibles;//Vector Supremo 

	Tablero(bool flag,int lvl=0)				//-1 negras(1er jugador), 1 rojas(2do jugador) -11 o 11 reina.
	{
		turno=flag;
		for(int i=0;i<tam;i++)
		{
			for(int j=0;j<tam;j++)
			{
				tabl[i][j]=0;
			}
		}
		//----------negras--------
		for(int i=0;i<tam;i+=2){tabl[0][i]=-1;}
		for(int i=1;i<tam;i+=2){tabl[1][i]=-1;}
		for(int i=0;i<tam;i+=2){tabl[2][i]=-1;}
		//----------rojas--------
		for(int i=1;i<tam;i+=2){tabl[7][i]=1;}
		for(int i=0;i<tam;i+=2){tabl[6][i]=1;}
		for(int i=1;i<tam;i+=2){tabl[5][i]=1;}

        fichas_rojas=12;
        fichas_negras=12;
        m_lvl=lvl;
	}

    Tablero(bool flag,int mat[tam][tam],int lvl=0)
    {
        turno=flag;
        equals_matrices(tabl,mat);
        fichas_rojas=12;
        fichas_negras=12;
        m_lvl=lvl;
    }



    void actualizar_num_fichas()
    {
        fichas_negras=0;
        fichas_rojas=0;
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                if(tabl[i][j]==1 || tabl[i][j]==11)fichas_rojas++;
                if(tabl[i][j]==-1 || tabl[i][j]==-11)fichas_negras++;
            }
        }
    }
	
	

//si explota es por culpa de este!,
//aparte... true si la ficha tiene al menos una movida |false
    bool puede_comer(int i,int j,int tab[tam][tam])/// 1 puede comer, 2 puede mover y 0 no puede hacer nada!
    {
    	int flag=0;
    	
    	bool he_comido=0;

    	vector< pair<int,int> > movimientosFicha;
    	if(turno)
    	{
    		if(tab[i][j] == -11)//si es que es una reina
    		{
    			if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    				{
    					tab[i-2][j-2]=-2;
    					movimientosFicha.push_back(make_pair(i-2,j-2));
    					flag++;
    					he_comido=1;
    					//return 1;
    				}
    			}

    			if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    				{
    					tab[i-2][j+2]=-2;
    					movimientosFicha.push_back(make_pair(i-2,j+2));

    					flag++;
    					he_comido=1;
    					//return 1;
    				}
    			}
    		}
    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] > 0 ))
    		{
    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
    			{
    				tab[i+2][j+2]=-2;
    				movimientosFicha.push_back(make_pair(i+2,j+2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] > 0 )
    		{
    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
    			{
    				tab[i+2][j-2]=-2;
    				movimientosFicha.push_back(make_pair(i+2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			if(tab[i][j] == -11)
    			{
		    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
		    		{ 
		    			tab[i-1][j-1]=-2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i-1,j-1));
		    		}
		    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
		    		{ 
		    			tab[i-1][j+1]=-2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i-1,j+1));
		    		}
    			}

	    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
	    		{
	    			tab[i+1][j+1]=-2; flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j+1));
	    		}
	    		if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    		{
	    			tab[i+1][j-1]=-2; flag++;/*return 2;*/
	    			movimientosFicha.push_back(make_pair(i+1,j-1));
	    		}
    		}
    	}
    	else
    	{
    		if(tab[i][j] == 11)
    		{
    			if( ( i+1<tam && j+1<tam && tab[i+1][j+1] < 0 ))
	    		{
	    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
	    			{
	    				tab[i+2][j+2]=2;
	    				movimientosFicha.push_back(make_pair(i+2,j+2));
	    				flag++;
	    				he_comido=1;
	    				//return 1;
	    			}
	    		}
	    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] < 0 )
	    		{
	    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
	    			{
	    				tab[i+2][j-2]=2;
	    				movimientosFicha.push_back(make_pair(i+2,j-2));
	    				flag++;
	    				he_comido=1;
	    				//return 1;
	    			}
	    		}
    		}
    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    			{
    				tab[i-2][j-2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j-2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}

    		if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    			{
    				tab[i-2][j+2]=2;
    				movimientosFicha.push_back(make_pair(i-2,j+2));
    				flag++;
    				he_comido=1;
    				//return 1;
    			}
    		}
    		if(!he_comido)
    		{
    			if(tab[i][j] == 11)
    			{
		    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 ))
		    		{
		    			tab[i+1][j+1]=2; flag++;/*return 2;*/
		    			movimientosFicha.push_back(make_pair(i+1,j+1));
		    		}
	    			if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 ))
	    			{
	    				tab[i+1][j-1]=2; flag++;/*return 2;*/
	    				movimientosFicha.push_back(make_pair(i+1,j-1));
	    			}
    			}

	    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 ))
	    		{
	    			tab[i-1][j-1]=2; flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j-1));
	    		}
	    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 ))
	    		{
	    			tab[i-1][j+1]=2; flag++;/*return 2*/;
	    			movimientosFicha.push_back(make_pair(i-1,j+1));
	    		}
    		}
    	}
    	if(flag!=0)
    	{
    		//jugadas.push_back(make_pair(i,j));
    		jugadas_posibles.push_back(make_pair(make_pair(i,j),movimientosFicha));
            return 1;
    		//movimientosFicha.push_back(i,j);//El último elemnto = ficha
    		//jugadas_posibles.push_back(movimientosFicha);
    	}
    	return 0;
    }

    void jugadas_permitidas()
    {
    	int dama,reina;
    	if(turno){dama=-1;reina=-11;}
    	else{dama=1;reina=11;}
    	int tab[tam][tam];
    	//cout<<"se igualo! prueba ->"<<tab[7][7]<<endl;
    	//equals_matrices(tab,tabl);
    	for(int i=0;i<tam;i++)
    	{
    		for(int j=0;j<tam;j++)
    		{
    			if(tabl[i][j]==dama || tabl[i][j]==reina)puede_comer(i,j,tab);
    			equals_matrices(tab,tabl);
    		}
    	}
    }


bool siguiente_jugada(int i_o,int j_o,int i_f,int j_f)
{
    //cout<<"entre!!!!!"<<endl;
    jugadas_posibles.clear();
    if(!puede_comer(i_o,j_o,tabl))return 0;
    vector< pair<int,int> >pos_finales;

    pos_finales=jugadas_posibles[0].second;
    int i;
    bool flag=0;
    pair<int,int>pos_final;
    pos_final=make_pair(i_f,j_f);
    for(i=0;i<pos_finales.size();i++)
    {
        if(pos_finales[i]==pos_final)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)return 0;


    int tmp;
    tmp=tabl[i_o][j_o];
    cout<<tabl[i_o][j_o]<<endl;
    tabl[i_o][j_o]=0;
    cout<<tabl[i_o][j_o]<<endl;
    if(abs(i_f-i_o)==2)
    {
        if(i_f-i_o>0 && j_f-j_o>0)tabl[i_o+1][j_o+1]=0;
        if(i_f-i_o>0 && j_f-j_o<0)tabl[i_o+1][j_o-1]=0;
        if(i_f-i_o<0 && j_f-j_o<0)tabl[i_o-1][j_o-1]=0;
        if(i_f-i_o<0 && j_f-j_o>0)tabl[i_o-1][j_o+1]=0;
    }
    tabl[i_f][j_f]=tmp;
    cout<<tabl[i_f][j_f]<<endl;

    m_lvl++;

    jugadas_posibles.clear();
    return 1;
}















}; 
