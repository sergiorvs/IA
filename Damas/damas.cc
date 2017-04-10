#include <iostream>
#include <vector>

using namespace std;

#define tam 8

void equals_matrices(int a[tam][tam],int b[tam][tam])
{
	for(int i=0;i<tam;i++)
	{
		for(int j=0;j<tam;j++)
		{
			a[i][j]=b[i][j];
		}
	}
}

class Tablero
{
public:
	int tabl[tam][tam];
	bool turno;				//1 es turno del primero, 0 del segndo
	vector< pair< int , int > > jugadas;
	Tablero(bool flag)				//-1 negras(1er jugador), 1 rojas(2do jugador) -11 o 11 reina.
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
	}
	
	void print_tablero()
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                cout<<"["<<tabl[i][j]<<" ]\t";
            }
            cout<<endl;
        }
    }

//si explota es por culpa de este!
    int puede_comer(int i,int j,int tab[tam][tam])/// 1 puede comer, 2 puede mover y 0 no puede hacer nada!
    {
    	int flag=0;
    	if(turno)
    	{
    		if(tab[i][j] == -11)
    		{
    			if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    				{
    					tab[i-2][j-2]=-2;
    					flag++;
    					//return 1;
    				}
    			}

    			if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] > 0 ))
    			{
    				if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    				{
    					tab[i-2][j+2]=-2;
    					flag++;
    					//return 1;
    				}
    			}

    			if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 )){ tab[i-1][j-1]=-2; flag++;/*return 2;*/}
    			if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 )){ tab[i-1][j+1]=-2; flag++;/*return 2;*/}
    		}
    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] > 0 ))
    		{
    			if( ( i+2<tam && j+2<tam && tab[i+2][j+2] == 0 ) )	
    			{
    				tab[i+2][j+2]=-2;
    				flag++;
    				//return 1;
    			}
    		}
    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] > 0 )
    		{
    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
    			{
    				tab[i+2][j-2]=-2;
    				flag++;
    				//return 1;
    			}
    		}

    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 )){tab[i+1][j+1]=-2; flag++;/*return 2;*/}
    		if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 )){tab[i+1][j-1]=-2; flag++;/*return 2;*/}
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
	    				flag++;
	    				//return 1;
	    			}
	    		}
	    		if( i+1<tam && j-1>=0 && tab[i+1][j-1] < 0 )
	    		{
	    			if( i+2<tam && j-2>=0 && tab[i+2][j-2] == 0 )
	    			{
	    				tab[i+2][j-2]=2;
	    				flag++;
	    				//return 1;
	    			}
	    		}
	    		if( ( i+1<tam && j+1<tam && tab[i+1][j+1] == 0 )){tab[i+1][j+1]=2; flag++;/*return 2;*/}
    			if( ( i+1<tam && j-1>=0 && tab[i+1][j-1] == 0 )){tab[i+1][j-1]=2; flag++;/*return 2;*/}
    		}
    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j-2>=0 && tab[i-2][j-2] == 0 ) )	
    			{
    				tab[i-2][j-2]=2;
    				flag++;
    				//return 1;
    			}
    		}

    		if( ( i-1>=0 && j+1<tam && tab[i-1][j-1] < 0 ))
    		{
    			if( ( i-2>=0 && j+2<tam && tab[i-2][j+2] == 0 ) )	
    			{
    				tab[i-2][j+2]=2;
    				flag++;
    				//return 1;
    			}
    		}
    		if( ( i-1>=0 && j-1>=0 && tab[i-1][j-1] == 0 )){tab[i-1][j-1]=2; flag++;/*return 2*/;}
    		if( ( i-1>=0 && j+1<tam && tab[i-1][j+1] == 0 )){tab[i-1][j+1]=2; flag++;/*return 2*/;}
    	}
    	if(flag!=0)jugadas.push_back(make_pair(i,j));
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
};

class minmax
{
 
};

int main()
{
	Tablero a(0);
	//cout<<a.tab[0][-1]<<endl;
	a.print_tablero();
	cout<<"-----------------------"<<endl;
	a.jugadas_permitidas();
	a.print_tablero();
	cout<<"-----------------------------"<<endl;
	cout<<"posibles jugadas"<<endl;
	for(int i=0;i<a.jugadas.size();i++)
	{
		cout<<"posicion: "<<a.jugadas[i].first<<", "<<a.jugadas[i].second<<endl;
	}

	int tab[tam][tam];
	equals_matrices(tab,a.tabl);
	a.puede_comer(5,1,tab);
	cout<<"-------------------------------------------"<<endl;
	a.print_tablero();

	return 0;
}