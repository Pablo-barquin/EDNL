#include "Util/alg_grafoPMC.h"

typedef unsigned int tcoste;
using namespace std;

tcoste KilometrosTotales(const GrafoP<tcoste>& G, vector<int> Parte, GrafoP<tcoste>::vertice Capital);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoDirigido.txt");

    cout << G;

    vector<int> Parte{4, 2, 0, 5, 3};
    GrafoP<tcoste>::vertice Capital = 0;

    tcoste Km = KilometrosTotales(G, Parte, Capital);

    cout << "Kilometros totales con el parte de trabajo actual: " << Km;
}

tcoste KilometrosTotales(const GrafoP<tcoste>& G, vector<int> Parte, GrafoP<tcoste>::vertice Capital)
{
    vector<GrafoP<tcoste>::vertice> P1;
    vector<tcoste> Capital_Destino = Dijkstra(G, Capital, P1);   // Calculamos los costes minimos de ir de Capital a todos los destinos

    // Como el grafo es dirigido, calculamos los costes de ir de todos los destinos de vuelta a la capital
    vector<GrafoP<tcoste>::vertice> P2;
    vector<tcoste> Destino_Capital = DijkstraInv(G, Capital, P2);

    // Sumamos el coste total de ir y volver
    vector<tcoste> ViajeCompleto;
    for(int i=0; i<Capital_Destino.size(); i++)
        ViajeCompleto.push_back(suma(Capital_Destino[i], Destino_Capital[i]));

    for(int i=0; i < Destino_Capital.size(); i++)
        cout << ViajeCompleto[i] << "  ";

    // Obtenemos los km totales realizando las cargas correspondientes del parte de trabajo
    tcoste TotalKm = 0;
    for(int i=0; i<ViajeCompleto.size(); i++)
        TotalKm += (ViajeCompleto[i] * Parte[i]);

    return TotalKm;
}