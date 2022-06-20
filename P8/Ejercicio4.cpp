#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

struct Canales
{
    GrafoP<tcoste>::vertice v, w;
    tcoste Longitud;
};

vector<Canales> AnadirCanales(const GrafoP<tcoste>& G);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoEj4.txt");
    GrafoP<tcoste> G_Max = PrimMax(G);

    vector<Canales> Solucion = AnadirCanales(G_Max);

    cout << "Los canales son los siguientes: " << endl;
    for(int i=0; i<Solucion.size(); i++)
        cout << "Ciudad " << Solucion[i].v << " -- Ciudad " << Solucion[i].w << " -- Longitud: " << Solucion[i].Longitud << endl;


}

vector<Canales> AnadirCanales(const GrafoP<tcoste>& G)
{
    int N = G.numVert();
    vector<Canales> Sol;
    for(int i=0; i<N; i++)
        for(int j=i; j<N; j++)
            if(G[i][j] != GrafoP<tcoste>::INFINITO)
            {
                Canales aux;
                aux.v = i;
                aux.w = j;
                aux.Longitud = G[i][j];

                Sol.push_back(aux);
            }    

    return Sol;
}