#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

//Multigrafo

typedef unsigned int tcoste;
using namespace std;

struct Solucion
{
    vector<GrafoP<tcoste>::vertice> P;
    tcoste CosteRecorrido;
};

Solucion TarifaMinima(const GrafoP<tcoste>&, const GrafoP<tcoste>&, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice, tcoste);
vector<GrafoP<tcoste>::vertice> CaminoHecho(GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino, vector<GrafoP<tcoste>::vertice> P);

int main()
{
    GrafoP<tcoste> Tren("Grafos/GrafoEj7 Tren.txt");
    GrafoP<tcoste> Bus("Grafos/GrafoEj7 Bus.txt");
    int Taxi = 10;
    GrafoP<tcoste>::vertice Origen = 0, Destino = 8;

    Solucion Final;
    Final = TarifaMinima(Tren, Bus, Origen, Destino, Taxi);

    cout << "La distancia minima entre origen y destino es: " << Final.CosteRecorrido << endl;
    cout << "El camino realizado es: " << endl;
    for(int i=0; i<Final.P.size(); i++)
        cout << "Paso " << (i+1) << "-> Nodo " << Final.P[i] << endl;

}

Solucion TarifaMinima(const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, GrafoP<tcoste>::vertice Origen, GrafoP<tcoste>::vertice Destino, tcoste Taxi)
{
    // Creamos un nuevo grafo de costes de 2*N nodos
    GrafoP<tcoste> NuevosCostes(2*Tren.numVert());

    // Rellenamos los valores
    for(int i=0; i<NuevosCostes.numVert(); i++)
    {
        for(int j=0; j<NuevosCostes.numVert(); j++)
        {
            // Rellenamos el cuadrante de trenes
            if(i < Tren.numVert() && j < Tren.numVert())
                NuevosCostes[i][j] = Tren[i][j];
            else if(i >= Bus.numVert() && j >= Bus.numVert())    // Rellenamos el cuadrante de buses
                NuevosCostes[i][j] = Bus[i-Bus.numVert()][j-Bus.numVert()];
            else if(j == i+Bus.numVert() || i == j+Bus.numVert())   // Rellenamos las posiciones con transbordos
                NuevosCostes[i][j] = Taxi;
            // Si ninguna se cumple, se deja en infinito
        }
    }

    // Obtenemos los costes minimos usando Dijkstra empezando desde el origen en bus o en tren
    vector<GrafoP<tcoste>::vertice> P1, P2;
    vector<tcoste> OrigenTren = Dijkstra(NuevosCostes, Origen, P1);
    vector<tcoste> OrigenBus = Dijkstra(NuevosCostes, Origen+Bus.numVert(), P2);

    // Obtenemos el menor coste terminando en tren o en bus desde los dos origenes
    Solucion sol;
    tcoste Final1, Final2;
    GrafoP<tcoste>::vertice v1 = Origen, w1, v2 =  Origen+Bus.numVert(), w2;

    // Ahora tengo que comparar los costes de empezar en tren y acabar en tren, y empezar en tren y acabar en bus
    if(OrigenTren[Destino] < OrigenTren[Destino+Bus.numVert()])
    {
        Final1 = OrigenTren[Destino];
        w1 = Destino;
    }
    else
    {
        Final1 = OrigenTren[Destino+Bus.numVert()];
        w1 = Destino+Bus.numVert();
    }

    // Ahora comparo los costes de empezar en bus y acabar en tren, y empezar en bus y acabar en bus
    if(OrigenBus[Destino] < OrigenBus[Destino+Bus.numVert()])
    {
        Final2 = OrigenBus[Destino];
        w2 = Destino;
    }
    else
    {
        Final2 = OrigenBus[Destino+Bus.numVert()];
        w2 = Destino+Bus.numVert();
    }

    if(Final1 < Final2)
    {
        sol.CosteRecorrido = Final1;
        sol.P = CaminoHecho(v1, w1, P1);
    }
    else
    {
        sol.CosteRecorrido = Final2;
        sol.P = CaminoHecho(v2, w2, P2);        
    }
    
    return sol;   
}

vector<GrafoP<tcoste>::vertice> CaminoHecho(GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino, vector<GrafoP<tcoste>::vertice> P)
{
    vector<GrafoP<tcoste>::vertice> Path, PathAux;

    PathAux.push_back(destino);
    
    do
    {
        PathAux.push_back(P[destino]);
        destino = P[destino];

    } while(destino != origen);

    while(PathAux.size() > 0)
    {
        Path.push_back(PathAux[PathAux.size()-1]);
        PathAux.pop_back();
    }

    return Path;
}