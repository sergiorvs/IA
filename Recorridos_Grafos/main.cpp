#include <iostream>
#include <time.h>     
#include <cmath>
#include <deque>
#include <iomanip>
#include <vector>

#include <GL/glut.h>

using namespace std;

#define INF 99999
#define numPuntos 200
#define rango 10

int up, down,left1,right1;
int ancho,alto;
float tamanno = 1.0f;


class Nodo{
public:
    int m_color;			//0 no visitado ,1 siendo visitado ,2 ya fue visitado
    pair<int,int> m_point;
    int m_d;
    Nodo* m_pi;				//de donde viene
    vector<Nodo*> m_adj;	//matriz de adyacencia
    vector<float> m_ponderado;	//ponderado correspondiente a cada adjunta
    Nodo(pair<int,int> pto)
    {
        m_point=pto;
        m_d = 0;
        m_color = 0;
        m_pi = NULL;
    }
};

vector< pair<int,int> > BFS(vector<Nodo*>& graph, int s,int f)//(grafo,nodo inicial)
{
    Nodo* u;
    Nodo* v;
    int i;
    vector< pair<int,int> > camino;
    for(int i = 0; i < graph.size(); i++)
    {
        graph[i]->m_color = 0;
        graph[i]->m_d = INF;
        graph[i]->m_pi = NULL;
    }
    graph[s]->m_color = 1;
    graph[s]->m_d = 0;
    graph[s]->m_pi = NULL;
    deque<Nodo*> Q;
    Q.push_front(graph[s]);
    while(!Q.empty())
    {
        u = Q.front();
        //cout<<u->m_id<<endl;
        for(i = 0; i < u->m_adj.size(); i++)
        {
            v = u->m_adj[i];
            if(v->m_color == 0)
            {
                v->m_color = 1;
                v->m_d = u->m_d+1;
                v->m_pi = u;
                Q.push_back(v);
            }
        }
        u->m_color = 2;
        camino.push_back(u->m_point);
        if(u->m_point == graph[f]->m_point)break;
       // cout<<u->m_id;
        Q.pop_front();
    }
    /*if(graph[i]->m_point != graph[f]->m_point)
    {
    	cout<<i<<endl;
    	cout<<"no se encontro recorrido"<<endl;
    	camino.clear();
    }*/
    return camino;
}

float distanciaEuclideana(pair<int,int> pto1,pair<int,int> pto2)
{
    return sqrt(pow(pto2.first-pto1.first,2)+pow(pto2.second-pto1.second,2));
}


vector<Nodo*> pintarPuntos()
{
    vector<Nodo*> graph;
    int pto_x , pto_y;
    glColor3f(1,2,5);
    glPointSize(12.5);
    glBegin(GL_POINTS);
    for(int i=0; i< numPuntos; i++)
    {
        pto_x = rand() % 100 ;
        pto_y = rand() % 100 ;
        pair<int,int> pto = make_pair(pto_x,pto_y);
        graph.push_back(new Nodo(pto));
        //cout<<pto_x<<" , "<<pto_y<<endl;
        glVertex3f(pto_x, pto_y, 0.0f);
    }
    glEnd();
    return graph;
}

vector<Nodo*> graph;

void llamarRecorrido()
{
    int init,end;
    /*ELigiendo Puntos Aleatorios Para Consulta*/
    init = rand() % numPuntos;
    end  = rand() % numPuntos;
    //hillClimbing(pto1,pto2,puntos); /*Si desean usar este, comenten el otro :3*/
    vector< pair<int,int> > camino;
    camino=BFS(graph,init,end);
    cout<<"INICIO: "<<graph[init]->m_point.first<<","<<graph[init]->m_point.second<<endl;
    cout<<"FIN: "<<graph[end]->m_point.first<<","<<graph[end]->m_point.second<<endl;
    cout<<"recorrido:"<<endl;
    for(int i=0;i<camino.size();i++)
    {
    	cout<<"("<<camino[i].first<<" , "<<camino[i].second<<") ;";
    }
}


void pintarAristas()
{
    graph = pintarPuntos();
    //pair<int,int> pto1 ,pto2;
    float distancia;
    //cout<<"Tamanio : "<<graph.size()<<endl;
    for(int i=0; i<graph.size();i++)
    {
    	for(int j=0; j<graph.size();j++)
    	{
    		distancia=distanciaEuclideana(graph[i]->m_point,graph[j]->m_point);
    		if(distancia<rango)
    		{
    			graph[i]->m_adj.push_back(graph[j]);
    			graph[i]->m_ponderado.push_back(distancia);
    			glColor3f(0,0,1);
                glBegin(GL_LINES);
                glVertex2f(graph[j]->m_point.first, graph[j]->m_point.second);
                glVertex2f(graph[i]->m_point.first, graph[i]->m_point.second);
                glEnd();
    		}
    	}
    }
    llamarRecorrido();
}

void reshape(int width, int height)
{
	ancho=width;alto=height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);
    glMatrixMode(GL_MODELVIEW);
    GLfloat formato;
    formato = (GLfloat)width / (GLfloat)height;
    if (width <= height) glOrtho (-10.0f*tamanno, 10.0f*tamanno, -10.0f*tamanno / formato, 10.0f*tamanno / formato, 1.0f, -1.0f);
    else glOrtho (-10.0f*tamanno * formato, 10.0f*tamanno * formato, -10.0f*tamanno, 10.0f*tamanno, 1.0f, -1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glLoadIdentity();
    glBegin(GL_QUADS);
        glVertex2i(100,100);
        glVertex2i(-100,100);
        glVertex2i(-100,-100);
        glVertex2i(100,-100);
    glEnd();
    pintarAristas();
    glFlush();

}

void Flechas(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 1;
   if (key==GLUT_KEY_DOWN) down = 1;
   if (key==GLUT_KEY_LEFT) left1 = 1;
   if (key==GLUT_KEY_RIGHT) right1 = 1;
}

void FlechasUp(int key, int x, int y) {
   if (key==GLUT_KEY_UP) up = 0;
   if (key==GLUT_KEY_DOWN) down = 0;
   if (key==GLUT_KEY_LEFT) left1 = 0;
   if (key==GLUT_KEY_RIGHT) right1 = 0;
}

void Zoom(int value) 
{
   if (up) tamanno = tamanno * 1.2;//1.01f;
   if (down) tamanno = tamanno / 1.2;//1.01f;
   /*if (left1)
   {
	costo=0;
	Llenos.clear();	
	puntos_recorridos.clear();
        camino.clear();	
	hill_climbing(grafo);
   }
  
   if(right1)
   {
	costo=0;
	Llenos.clear();	
	puntos_recorridos.clear();
        camino.clear();	
	a_asterisco(grafo);
   }*/
    reshape(ancho,alto);
    glutTimerFunc(33,Zoom,1);
    glutPostRedisplay();
    
}

void init()
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(0,0);
}


int main(int argc, char **argv)
{
	//cout<<"hello word"<<endl;
    srand (time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(2000, 1200);
    glutCreateWindow("Hello OpenGL");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
  //  glutTimerFunc(33,Zoom,1);
    glutSpecialFunc(Flechas);
    glutSpecialUpFunc(FlechasUp);
    /*vector< pair<int,int> > camino;
	cout<<graph.size()<<endl;
	//int ini=rand()%graph.size();
	//int fin=rand()%graph.size();
	camino=BFS(graph,1,20);*/
    glutMainLoop();

    return 0;
}