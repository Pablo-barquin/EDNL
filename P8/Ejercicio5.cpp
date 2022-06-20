#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

tcoste FibraMinima(const GrafoP<tcoste> G);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoEj4.txt");

    tcoste Final = FibraMinima(G);
    
    cout << "El coste minimo de Fibra es: " << Final;
}

tcoste FibraMinima(const GrafoP<tcoste> G)
{
    // Obtengo el camino mínimo posible
    GrafoP<tcoste> G_Min = Kruskall(G);

    // Obtengo el coste minimo
    tcoste min = 0;
    int N = G.numVert();
    for(int i=0; i<N; i++)
        for(int j=i; j<N; j++)
            if(G_Min[i][j] != GrafoP<tcoste>::INFINITO)
                min += G_Min[i][j];
    
    return min;
}