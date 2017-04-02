#include <iostream>
#include <vector>

using namespace std;
#define tam 4

class Tablero{
  public:
    int mat[tam][tam];
    int reinas=0;
    vector<Tablero*> m_child;
    Tablero(int r)
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                mat[i][j] =0;
            }
        }
        reinas=r;
    }
    
    ///copia la matris anterior e inserta nueva ficha
    void siguiente_jugada(int matrix[tam][tam],int fil,int col)
    {
      for(int i=0;i<tam;i++)
      {
        for(int j=0;j<tam;j++)
        {
          mat[i][j]=matrix[i][j];
        }
      }
      
      insertar(fil,col);
    }
    void insertar(int fil,int col)
    {
        int af=fil;int ac=col;
        for(int i=0;i<tam;i++)
        {
            mat[i][col]=-1;
            mat[fil][i]=-1;
            
        }
        
        //diagonales
        //for(int i=fil)
        while(af > 0 && ac > 0){af--;ac--; mat[af][ac]=-1;}ac=col;af=fil;
        while(af < tam-1 && ac < tam-1){af++;ac++; mat[af][ac]=-1;}ac=col;af=fil;
        while(af > 0 && ac < tam-1){af--;ac++; mat[af][ac]=-1;}ac=col;af=fil;
        while(af < tam-1 &&  ac > 0){af++;ac--; mat[af][ac]=-1;}
        mat[fil][col]=1;
        reinas++;
    }
    
    bool analizarJugada()
    {
        for(int i=0;i<tam;i++)
        {
          for(int j=0;j<tam;j++)
          {
            if(mat[i][j]==0)return true;
          }
        }
        return false;
    }
    void print_tablero()
    {
        for(int i=0;i<tam;i++)
        {
            for(int j=0;j<tam;j++)
            {
                cout<<"["<<mat[i][j]<<" ]\t";
            }
            cout<<endl;
        }
    }
};
vector<Tablero* >q;
class Arbol{
    public:
        Tablero* m_root;
        
        //int filReyna, colReyna;
        Arbol(int i,int j)
        {
          m_root=NULL;
          m_root=new Tablero(0);
          m_root->insertar(i,j);
        }
        
        void insertar_reina(Tablero* aux)
        {
            
            for(int i=0;i<tam;i++)
            {
              for(int j=0;j<tam;j++)
              {
                if(aux->mat[i][j]==0)
                {
                  aux->m_child.push_back(new Tablero(aux->reinas));
                  aux->m_child[aux->m_child.size()-1]->siguiente_jugada(aux->mat,i,j);
                }
              }
            }
            insert_all(aux);
                    
          
        }
        
        void insert_all(Tablero* aux)
        {
            
            if(aux->analizarJugada())
            {
             
                for(int i=0;i< aux->m_child.size() ; i++)
                {
                    //cout<<"i: "<<i<<endl;
                    //cout<<"hijos: "<<aux->m_child.size()<<endl;
                    aux=aux->m_child[i];
                    q.push_back(aux);
                    //if(aux->m_child[i]) insertar_reina(aux->m_child[i]);
                }
            }
            while(q.size()>0)
            {
                Tablero* tmp;
                tmp=q[q.size()-1];
                q.pop_back();
                insertar_reina(tmp);
            }        

             
        }
};
int main()
{
    Arbol a(0,0);
    
    a.m_root->print_tablero();
    cout<<"-------------------------------------------------\n"<<endl;
    a.insertar_reina(a.m_root);
    a.insert_all(a.m_root);
    cout<<a.m_root->m_child.size()<<endl;
    cout<<a.m_root->m_child[1]->m_child.size()<<endl;
    a.m_root->m_child[1]->print_tablero();
    cout<<"-------------------------------------------------\n"<<endl;
    a.m_root->m_child[1]->m_child[0]->print_tablero();
    //a.m_root->m_child[0]->m_child[0]->print_tablero();
    //cout<<"reinas puestas: "<<a.m_root->m_child[0]->m_child[0]->m_child[0]->m_child[0]->reinas<<endl;

    return 0;
}




























