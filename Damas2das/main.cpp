#include "Tablero.h"
#include <queue> 

class miniMax
{
public:
    Tablero* mRoot;
    int** mTablerito;
    int mMaxLevel;
    bool mTurno;
    miniMax(int** matriz,bool turno,int level)
    {
        mTablerito= new int*[tam];
        for(int i=0;i<tam;i++)
        {
            mTablerito[i]=new int[tam];
        }
        mRoot = NULL;
        igualarMatrices(mTablerito,matriz);
        mMaxLevel = level;
        mTurno =  turno;
        mRoot= new Tablero(mTablerito,mTurno,0);
    }


    void construirArbolNivelBase()
    {
        vector<Tablero* > next_jugadas;
        Tablero *aux;
        next_jugadas.push_back(mRoot);
        while(next_jugadas.size()>0)
        {
            aux=next_jugadas[0];
            //cout<<"maxlevel"<<mRoot->mNivelMinMax<<endl;
            //cout<<"entro"<<endl;
            if(aux->mNivelMinMax>mMaxLevel)break;
            next_jugadas.erase(next_jugadas.begin());
            aux->realizarJugada();
            Tablero* ptr;
            for(int i=0;i<aux->mTablerosUpdate.size();i++)
            {
                ptr=new Tablero(aux->mTablerosUpdate[i],!aux->mTurno,aux->mNivelMinMax+1);
                ptr->mParent=aux;                
                aux->mChild.push_back(ptr);
                next_jugadas.push_back(ptr);
            }
        }

    }

    Tablero* minmax()
    {
        deque<Tablero *> aux;
        aux.push_front(mRoot);
        Tablero* tmp=mRoot;
        //bool flag=1;        //1 maximizador, 0 minimizador
        while(!aux.empty())
        {
            
            

            for(int i=0;i<tmp->mChild.size();i++)
            {
                aux.push_front(tmp->mChild[i]);
            }
            tmp=aux.front();
                //cout<<"hola"<<endl;
            
            if(tmp->mChild.size() == 0)
            {
                
                if(tmp->mParent->mNivelMinMax % 2!= 0)  ///minimizador
                {
                    if(tmp->mParent->alfa < tmp->mParent->betha)
                    {
                        if(tmp->mParent->betha>tmp->valor)
                        {
                            tmp->mParent->betha = tmp->valor;
                            tmp->mParent->vertice = tmp->valor;

                        }

                        
                    }
                }
                else
                {

                    if(tmp->mParent->alfa > tmp->mParent->betha)
                    {
                        if(tmp->mParent->alfa>tmp->valor)
                        {
                            tmp->mParent->alfa = tmp->valor;
                            tmp->mParent->vertice = tmp->valor;
                        }
                    }   
                    
                }
                
                if(tmp->mParent != mRoot )
                    aux.pop_front();            
            }
         
         
        
    }
    }


   /* void construirArbolNivelBase()
    {
        mRoot= new Tablero(mTablerito,mTurno,0);
        mRoot->realizarJugada();
        Tablero* ptr;
        for(int i=0;i<mRoot->mTablerosUpdate.size();i++)
        {
            ptr = new Tablero(mRoot->mTablerosUpdate[i],!mTurno,mRoot->mNivelMinMax+1);
            mRoot->mChild.push_back(ptr);
            construirArbolNivelMaximo(mRoot);
        }
    }

    void construirArbolNivelMaximo(Tablero* &ptr)
    {
        for(int i=0; i<ptr->mChild.size();i++)
        {
            if(ptr->mChild[i]->mNivelMinMax <= mMaxLevel)
            {
                ptr->mChild[i]->realizarJugada();

                Tablero* aux;
                for(int j=0;j<ptr->mChild[i]->mTablerosUpdate.size();j++)
                {
                    aux = new Tablero(ptr->mChild[i]->mTablerosUpdate[j],!(ptr->mChild[ei]->mTurno),ptr->mChild[i]->mNivelMinMax+1);
                    ptr->mChild[i]->mChild.push_back(aux);
                }
                Tablero *ptr1 =ptr->mChild[i];
                construirArbolNivelMaximo(ptr1);
            }


        }
    }*/

};
int main() {

    int** tabl;
    tabl= new int*[tam];
    for(int i=0;i<tam;i++)
    {
        tabl[i]=new int[tam];
    }
    //int tabl[tam][tam];
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

    cout<<"Matriz Original: "<<endl;
    /*cout<<"**********************************************************"<<endl;
    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            cout<<"["<<tabl[i][j]<<" ]\t";
        }
        cout<<endl;
    }
    cout<<"**********************************************************"<<endl;*/
    /*Tablero tablerito(tabl,0,0);
    tablerito.realizarJugada();*/
    /*tabl[2][0]=0;
    tabl[4][2]=-1;*/
    miniMax arbol(tabl,0,1);
    arbol.construirArbolNivelBase();
    cout<<"Imprimiendo Hijos "<<endl;
    /*for(int i=0;i<arbol.mRoot->mChild.size();i++)
    {
        cout<<"Turno "<<arbol.mRoot->mChild[i]->mTurno<<" Level: "<<arbol.mRoot->mChild[i]->mNivelMinMax<<endl;
        printTablero(arbol.mRoot->mChild[i]->mTablero);
    }*/
    //printTablero(arbol.mRoot->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mChild[0]->mTablero);
    //printTablero(arbol.mRoot->mChild[0]->mChild[0]->mChild[0]->mTablero);
    arbol.minmax();
    return 0;
}   