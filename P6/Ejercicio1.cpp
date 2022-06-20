#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

using namespace std;

typedef unsigned int tCoste;

int main()
{
    GrafoP<tCoste> G("Grafos/GrafoNegativo.txt");

    cout << G << endl;

    vector<typename GrafoP<tCoste>::vertice> P;

    vector<tCoste> Costes = Dijkstra(G, 0, P);

    cout << Costes << endl;
    cout << P;
}
