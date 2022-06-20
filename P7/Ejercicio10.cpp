#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

struct Solucion
{
    tcoste CosteRecorrido;
    vector<GrafoP<tcoste>::vertice> P;
};

Solucion TarifaMinima(const GrafoP<tcoste>& Avion, const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, GrafoP<tcoste>::vertice Origen, GrafoP<tcoste>::vertice Destino, int TaxiEstacion, int TaxiAeropuerto);
vector<GrafoP<tcoste>::vertice> CaminoHecho(GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino, vector<GrafoP<tcoste>::vertice> P);
tcoste MejorRuta(tcoste uno, tcoste dos, tcoste tres, GrafoP<tcoste>::vertice Destino, int N, GrafoP<tcoste>::vertice &w);

int main()
{
    GrafoP<tcoste> Avion("Grafos/GrafoEj7 Avion.txt");
    GrafoP<tcoste> Bus("Grafos/GrafoEj7 Bus.txt");
    GrafoP<tcoste> Tren("Grafos/GrafoEj7 Tren.txt");
    GrafoP<tcoste>::vertice Origen = 0, Destino = 8;
    int TaxiEstaciones = 15, TaxiAeropuerto = 30;

    Solucion sol = TarifaMinima(Avion, Tren, Bus, Origen, Destino, TaxiEstaciones, TaxiAeropuerto);

    cout << "El coste minimo del viaje es: " << sol.CosteRecorrido << endl;
    cout << "La ruta elegida es: " << endl;
    for(int i=0; i<sol.P.size(); i++)
        cout << "Paso " << (i+1) << ": Nodo " << sol.P[i] << endl;

}

Solucion TarifaMinima(const GrafoP<tcoste>& Avion, const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, GrafoP<tcoste>::vertice Origen, GrafoP<tcoste>::vertice Destino, int TaxiEstacion, int TaxiAeropuerto)
{
    // Número de nodos
    int N = Avion.numVert();

    // Vamos a unir en un grafo todos los costes
    GrafoP<tcoste> NuevosCostes(3*N);

    for(int i=0; i<NuevosCostes.numVert(); i++)
        for(int j=0; j<NuevosCostes.numVert(); j++)
        {
            if(i < N && j < N)    // Añado los costes de viajar en tren entre vertices
                NuevosCostes[i][j] = Tren[i][j];
            else if((i >= N && i < 2*N) && (j >= N && j < 2*N))   // Añado los costes de viajar en bus entre vertices
                NuevosCostes[i][j] = Bus[i-N][j-N];
            else if(i >= 2*N && j >= 2*N)   // Añado los costes de viajar en avion entre vertices
                NuevosCostes[i][j] = Avion[i-(2*N)][j-(2*N)];
            else if((j < 2*N && i < 2*N) && (i == j+N || j == i+N))   // Añadimos los costes de taxi entre estaciones de bus y taxi
                NuevosCostes[i][j] = TaxiEstacion;
            else if(i == j+(2*N) || j == i+(2*N) || i == j+N || j == i+N)   // Añadimos los costes de aeropuerto a las estaciones de bus y taxi
                    NuevosCostes[i][j] = TaxiAeropuerto;
        }

        vector<GrafoP<tcoste>::vertice> P1, P2, P3;
        // Obtenemos el vector de costes minimos usando Dijstra desde los 3 origenes distintos
        vector<tcoste> InicioTren = Dijkstra(NuevosCostes, Origen, P1);
        vector<tcoste> InicioBus = Dijkstra(NuevosCostes, Origen+N, P2);
        vector<tcoste> InicioAvion = Dijkstra(NuevosCostes, Origen+(2*N), P3);

        // Obtenemos el camino y el coste minimo
        GrafoP<tcoste>::vertice v1, v2, v3;
        tcoste Final1, Final2, Final3, aux, MINIMO;
        Final1 = MejorRuta(InicioTren[Destino], InicioTren[Destino+N], InicioTren[Destino+2*N], Destino, N, v1);
        Final2 = MejorRuta(InicioBus[Destino], InicioBus[Destino+N], InicioBus[Destino+2*N], Destino, N, v2);
        Final3 = MejorRuta(InicioAvion[Destino], InicioAvion[Destino+N], InicioAvion[Destino+2*N], Destino, N, v3);

        MINIMO = min(Final1, min(Final2, Final3));

        Solucion sol;
        sol.CosteRecorrido = MINIMO;
        if(MINIMO == Final1) sol.P = CaminoHecho(Origen, v1, P1);
        else if(MINIMO == Final2) sol.P = CaminoHecho(Origen+N, v2, P2);
        else sol.P = CaminoHecho(Origen+2*N, v3, P3);

        return sol;
}

tcoste MejorRuta(tcoste uno, tcoste dos, tcoste tres, GrafoP<tcoste>::vertice Destino, int N, GrafoP<tcoste>::vertice &w)
{
    tcoste Final = min(uno, min(dos, tres));
    if(Final == uno) w = Destino;
    else if(Final == dos) w = Destino+N;
    else w = Destino+2*N;

    return Final;
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