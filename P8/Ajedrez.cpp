#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

struct Casilla
{
    int X, Y;
};

struct Solucion
{
    tcoste Coste;
    vector<Casilla> Casillas;
};

Solucion AjedrezMinimo(int N, Casilla Origen, Casilla Destino);
Casilla Nodo_to_Casilla(int N, GrafoP<tcoste>::vertice n);
bool MovimientoCaballo(Casilla A, Casilla B);
GrafoP<tcoste>::vertice Casilla_to_Nodo(int N, Casilla A);
vector<Casilla> CaminoCasillas(vector<GrafoP<tcoste>::vertice> P, int N, GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino);

int main()
{
    Casilla Origen, Destino;
    Origen.X = 0; Origen.Y = 0;
    Destino.X = 0; Destino.Y = 1;
    Solucion Final = AjedrezMinimo(4, Origen, Destino);

    cout << "El numero de pasos para llegar es: " << Final.Coste << endl;
    cout << "Las casillas usadas son: " << endl;
    for(int i=0; i < Final.Casillas.size(); i++)
        cout << "Paso " << i << ": [" << Final.Casillas[i].X << ", " << Final.Casillas[i].Y << "]" << endl;
}

Solucion AjedrezMinimo(int N, Casilla Origen, Casilla Destino)
{
    // Creo un grafo de tamaño N*N nodos
    GrafoP<tcoste> Tablero(N*N);

    // Vamos a rellenar este Tablero comprobando desde una casilla, a que casillas se pueden ir realizando el movimiento del caballo
    for(int i=0; i<Tablero.numVert(); i++)
        for(int j=0; j<Tablero.numVert(); j++)
        {
            Casilla A = Nodo_to_Casilla(N, i);
            Casilla B = Nodo_to_Casilla(N, j);
            if(MovimientoCaballo(A, B))
                Tablero[i][j] = 1;
            else
                Tablero[i][j] = GrafoP<tcoste>::INFINITO;
        }

    // Rellenando el tablero con los movimientos posibles desde una casilla a las demas, obtenemos el coste y el camino
    GrafoP<tcoste>::vertice o = Casilla_to_Nodo(N, Origen), d = Casilla_to_Nodo(N, Destino);
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> CosteMinimo = Dijkstra(Tablero, o, P);

    Solucion sol;
    sol.Coste = CosteMinimo[d];

    sol.Casillas = CaminoCasillas(P, N, o, d);

    return sol;
}

Casilla Nodo_to_Casilla(int N, GrafoP<tcoste>::vertice n)
{
    Casilla A;
    A.X = n/N;    A.Y = n%N;

    return A;
}

bool MovimientoCaballo(Casilla A, Casilla B)
{
    return (abs(A.X - B.X) == 2 && abs(A.Y - B.Y) == 1) || (abs(A.X - B.X) == 1 && abs(A.Y - B.Y) == 2);
}

GrafoP<tcoste>::vertice Casilla_to_Nodo(int N, Casilla A)
{
    return A.X * N + A.Y;
}

vector<Casilla> CaminoCasillas(vector<GrafoP<tcoste>::vertice> P, int N, GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino)
{
    vector<Casilla> Aux, Aux2;


    Aux.push_back(Nodo_to_Casilla(N, destino));
    do
    {
        Aux.push_back(Nodo_to_Casilla(N, P[destino]));
        destino = P[destino];
    }while(origen != destino);
    
    while(Aux.size() > 0)
    {
        Aux2.push_back(Aux[Aux.size()-1]);
        Aux.pop_back();
    }

    return Aux2;
}