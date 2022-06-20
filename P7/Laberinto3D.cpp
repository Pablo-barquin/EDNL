#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;

struct Casilla
{
    int x,y,z;
};

struct Pared
{
    Casilla cas1, cas2;
};

tcoste CaminoLaberinto(int N, vector<Pared> Paredes, Casilla  Origen, Casilla Destino, vector<Casilla> &Camino);
GrafoP<tcoste>::vertice CasillatoNodo(int N, Casilla C1);
Casilla NodotoCasilla(int N, GrafoP<tcoste>::vertice nodo);
vector<Casilla> CaminoRecorrido(int N, vector<GrafoP<tcoste>::vertice> Path, Casilla Origen, Casilla Destino);
bool CasillaAdyacente(Casilla A, Casilla B);
vector<Pared> ConstruirParedes();

int main()
{
    int N = 2;
    Casilla Origen, Destino;
    Origen.x = 0; Origen.y = 0; Origen.z = 0;
    Destino.x = 0; Destino.y = 0; Destino.z = 1;

    vector<Casilla> Path;
    vector<Pared> Paredes = ConstruirParedes();
    
    tcoste CosteCamino = CaminoLaberinto(N, Paredes, Origen, Destino, Path);

    std::cout << "El coste del camino es: " << CosteCamino << std::endl;

    std::cout << "El recorrido del camino es: " << std::endl;
    for(int i=0; i<Path.size(); i++)
        std::cout << "Casilla [" << Path[i].x << ", " << Path[i].y << ", " << Path[i].z << "]" << std::endl;
}

tcoste CaminoLaberinto(int N, vector<Pared> Paredes, Casilla Origen, Casilla Destino, vector<Casilla> &Camino)
{
    // Creamos un Grafo de tamaño N*N*N para representar el laberinto 3D
    GrafoP<tcoste> G(N*N*N);

    // Rellenamos el grafo con las adyacencias posibles que tiene
    for(int i=0; i<G.numVert(); i++)
        for(int j=0; j<G.numVert(); j++)
        {
            Casilla Aux1 = NodotoCasilla(N, i);
            Casilla Aux2 = NodotoCasilla(N, j);
            if(CasillaAdyacente(Aux1, Aux2))
                G[i][j] = 1;
            else
                G[i][j] = GrafoP<tcoste>::INFINITO;
        }

    // Sabiendo las adyacencias posibles, añadimos las paredes
    for(int i=0; i<Paredes.size(); i++)
    {
        GrafoP<tcoste>::vertice Aux1 = CasillatoNodo(N, Paredes[i].cas1), Aux2 = CasillatoNodo(N, Paredes[i].cas2);
        G[Aux1][Aux2] = G[Aux2][Aux1] = GrafoP<tcoste>::INFINITO;
    }

    // Utilizamos Dijkstra desde el origen
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> CosteMin = Dijkstra(G, CasillatoNodo(N, Origen), P);

    tcoste MinimoDestino = CosteMin[CasillatoNodo(N, Destino)];

    Camino = CaminoRecorrido(N, P, Origen, Destino);

    return MinimoDestino;        
}

GrafoP<tcoste>::vertice CasillatoNodo(int N, Casilla A)
{
    return A.x*N + A.y + A.z*N*N;
}

Casilla NodotoCasilla(int N, GrafoP<tcoste>::vertice V)
{
    Casilla Aux;
    
    tcoste Z = V%(N*N);
    
    Aux.z = V/(N*N);
    Aux.y = Z%N;
    Aux.x = Z/N;

    return Aux;
}

bool CasillaAdyacente(Casilla C1, Casilla C2)
{
    if(abs(C1.x - C2.x) == 1 && abs(C1.y - C2.y) == 0 && abs(C1.z - C2.z) == 0)
        return true;
    else if(abs(C1.x - C2.x) == 0 && abs(C1.y - C2.y) == 1 && abs(C1.z - C2.z) == 0)
        return true;
    else if(abs(C1.x - C2.x) == 0 && abs(C1.y - C2.y) == 0 && abs(C1.z - C2.z) == 1)
        return true;
    else return false;
}

vector<Casilla> CaminoRecorrido(int N, vector<GrafoP<tcoste>::vertice> P, Casilla Origen, Casilla Destino)
{
    GrafoP<tcoste>::vertice ori = CasillatoNodo(N, Origen), des = CasillatoNodo(N, Destino);

    vector<Casilla> Aux, CaminoAux;

    CaminoAux.push_back(Destino);

    do
    {
        des = P[des];
        CaminoAux.push_back(NodotoCasilla(N, des));
    }while(des != ori);

    while(CaminoAux.size() > 0)
    {
        Aux.push_back(CaminoAux[CaminoAux.size()-1]);
        CaminoAux.pop_back();
    }

    return Aux;
}

vector<Pared> ConstruirParedes()
{
    vector<Pared> Auxiliar;

    std::cout << "Pulsa -1, al finalizar un pared, para parar" << std::endl;
    int stop;
    do
    {
        Pared P1;
        std::cout << "Casilla 1" << std::endl;
        std::cout << "  -X: "; std::cin >> P1.cas1.x;
        std::cout << "  -Y: "; std::cin >> P1.cas1.y; 
        std::cout << "  -Z: "; std::cin >> P1.cas1.z; 

        std::cout << "Casilla 2" << std::endl;
        std::cout << "  -X: "; std::cin >> P1.cas2.x;
        std::cout << "  -Y: "; std::cin >> P1.cas2.y; 
        std::cout << "  -Z: "; std::cin >> P1.cas2.z; 

        Auxiliar.push_back(P1);
        std::cout << "Parar? "; std::cin >> stop;
    }while(stop != -1);
    
    return Auxiliar;
}