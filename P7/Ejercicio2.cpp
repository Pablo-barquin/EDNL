#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

struct Casilla
{
    int fil, col;
};

struct Paredes
{
    Casilla pos1, pos2;
};

typedef unsigned int tcoste;
using namespace std;

vector<Paredes> ConstruirParedes(int N);
vector<Casilla> EncontrarCamino(int N, vector<Paredes> P, Casilla entrada, Casilla destino);
vector<Casilla> CaminoCasillas(int N, typename GrafoP<tcoste>::vertice origen, typename GrafoP<tcoste>::vertice destino, const vector<GrafoP<tcoste>::vertice>& P);
Casilla Nodo_A_Casilla(int N, typename GrafoP<tcoste>::vertice nodo);
GrafoP<tcoste>::vertice Casilla_A_Nodo(int N, Casilla Caux);
bool CasillaAdyacente(Casilla C1, Casilla C2);

int main()
{
    int N = 4;
    vector<Paredes> P = ConstruirParedes(N);

    Casilla inicio, final;
    inicio.fil = 0; inicio.col = 0;
    final.fil = 3; final.col = 3;

    vector<Casilla> Camino = EncontrarCamino(N, P, inicio, final);

    cout << "Longitud del camino: " << Camino.size() << endl;
    for(int i=0; i<Camino.size(); i++)
        cout << "Paso " << (i+1) << ": [" << Camino.at(i).fil << ", " << Camino.at(i).col << "]" << endl; 
}

vector<Paredes> ConstruirParedes(int N)
{
    cout << "INDICAR EL PAR DE CASILLAS QUE QUIERES UNA PARED: " << endl;

    Paredes P;
    vector<Paredes> Pared;
    int x;
    do
    {
        cout << "Casilla 1 - Fila: ";
        cin >> P.pos1.fil;
        cout << "Casilla 1 - Col: ";
        cin >> P.pos1.col;
        cout << endl;
        cout << "Casilla 2 - Fila: ";
        cin >> P.pos2.fil;
        cout << "Casilla 2 - Col: ";
        cin >> P.pos2.col;

        Pared.push_back(P);
        cout << "Escribe -1 si desea parar. Otro numero si desea añadir otro par de casillas: ";
        cin >> x;
    }while(x != -1);
    
    return Pared;
}


vector<Casilla> EncontrarCamino(int N, vector<Paredes> P, Casilla entrada, Casilla destino)
{
    GrafoP<tcoste> GrafoTablero(N*N);   //Creamos un grafo de N^2 nodos 
    matriz<int> Tablero(N, 0);  //Creamos una matriz NxN que representa el laberinto

    tcoste inf = GrafoP<tcoste>::INFINITO;
    //Rellenamos el grafo comprobando sus casillas adyacentes
    for(int i=0; i<GrafoTablero.numVert(); i++)
        for(int j=0; j<GrafoTablero.numVert(); j++)
        {
            GrafoTablero[i][j] = 1;
            if(i == j)
                GrafoTablero[i][j] = 0;
            else if(!CasillaAdyacente(Nodo_A_Casilla(N, i), Nodo_A_Casilla(N, j)))
                GrafoTablero[i][j] = inf;
        }

    typename GrafoP<tcoste>::vertice v1, v2;
    //Rellenamos el grafo con las paredes en el laberinto
    for(int i=0; i<P.size(); i++)
    {
        v1 = Casilla_A_Nodo(N, P.at(i).pos1);
        v2 = Casilla_A_Nodo(N, P.at(i).pos2);

        GrafoTablero[v1][v2] = inf;
        GrafoTablero[v2][v1] = inf;
    }

    cout << GrafoTablero;

    vector<GrafoP<tcoste>::vertice> Path;
    vector<tcoste> VDijkstra = Dijkstra(GrafoTablero, Casilla_A_Nodo(N, entrada), Path);

    vector<Casilla> Final = CaminoCasillas(N, Casilla_A_Nodo(N, entrada), Casilla_A_Nodo(N, destino), Path);

    return Final;
}

vector<Casilla> CaminoCasillas(int N, typename GrafoP<tcoste>::vertice origen, typename GrafoP<tcoste>::vertice destino, const vector<GrafoP<tcoste>::vertice>& P)
{
    vector<Casilla> Camino, CaminoAux;

    CaminoAux.push_back(Nodo_A_Casilla(N, destino));
    do {
        CaminoAux.push_back(Nodo_A_Casilla(N, P[destino]));
        destino = P[destino];
    } while (destino != origen);

    while(CaminoAux.size() != 0)
    {
        Camino.push_back(CaminoAux.at(CaminoAux.size()-1));
        CaminoAux.pop_back();
    }

    return Camino;
}

Casilla Nodo_A_Casilla(int N, typename GrafoP<tcoste>::vertice nodo)
{
    Casilla Aux;
    Aux.fil = nodo / N;  //Sacamos la fila del nodo
    Aux.col = nodo % N;  //Sacamos la columna del vertice

    return Aux; //Devolvemos la casilla correspondiente
}

GrafoP<tcoste>::vertice Casilla_A_Nodo(int N, Casilla Caux)
{
    return (Caux.fil * N + Caux.col);   //Devolvemos el nodo correspondiente
}

bool CasillaAdyacente(Casilla C1, Casilla C2)
{
    return ((abs(C1.fil - C2.fil) == 1 && C1.col == C2.col) || (C1.fil == C2.fil && abs(C1.col - C2.col) == 1));
}

/*
    - Tablero: NxN
    - Grafo N^2 nodos
    - Casilla: fila y columna
    - Pared: Pareja de Casillas

    Casilla Nodo_to_Casilla(N, nodo)    
    nodo Casilla_to_nodo(N, casilla)

    Devolver camino de casillas, no de nodos
*/