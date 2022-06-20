#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"

typedef unsigned int tcoste;
using namespace std;

struct Puente
{
    GrafoP<tcoste>::vertice FobosV, DeimosV;
};

Puente ConstruirPuente(const GrafoP<tcoste>& F, const GrafoP<tcoste>& D, vector<GrafoP<tcoste>::vertice> C1, vector<GrafoP<tcoste>::vertice> C2);
tcoste CosteGlobal(const matriz<tcoste>& G);

int main()
{
    GrafoP<tcoste> Fobos("Grafos/GrafoEj12 Fobos.txt");
    GrafoP<tcoste> Deimos("Grafos/GrafoEj12 Deimos.txt");

    vector<GrafoP<tcoste>::vertice> C1{0,1,3,4}, C2{0,2};

    Puente Final = ConstruirPuente(Fobos, Deimos, C1, C2);

    cout << "Los puentes que hacen el menor coste global es:" << endl;
    cout << "Ciudad " << Final.DeimosV << " en Deimos" << endl;
    cout << "Ciudad " << Final.FobosV << " end Fobos" << endl;
}

Puente ConstruirPuente(const GrafoP<tcoste>& F, const GrafoP<tcoste>& D, vector<GrafoP<tcoste>::vertice> C1, vector<GrafoP<tcoste>::vertice> C2)
{
    // Unimos en un grafo los dos archipielagos
    int N1 = F.numVert(), N2 = D.numVert();
    GrafoP<tcoste> Grecoland(N1+N2);

    // Rellenamos el grafo con los datos que tenemos actualmente
    for(int i=0; i<Grecoland.numVert(); i++)
        for(int j=0; j<Grecoland.numVert(); j++)
            if(i < N1 && j < N1)    // Añadimos los costes de Fobos
                Grecoland[i][j] = F[i][j];
            else if(i >= N1 && j >= N1)     // Añadimos los costes de Deimos
                Grecoland[i][j] = D[i-N1][j-N1]; 

    // Construimos todos los puentes posibles y vamos comprobando cual es el puente que hace el menor coste global
    Puente sol;
    tcoste min = GrafoP<tcoste>::INFINITO, aux; 
    GrafoP<tcoste> AuxiliarGrecoland = Grecoland;
    matriz<tcoste> MinFloyd;

    matriz<GrafoP<tcoste>::vertice> P;
    for(int i=0; i<C1.size(); i++)
        for(int j=0; j<C2.size(); j++)
        {
            AuxiliarGrecoland[C1[i]][C2[j]+N1] = 0;
            AuxiliarGrecoland[C2[j]+N1][C1[i]] = 0;
            MinFloyd = Floyd(AuxiliarGrecoland, P);
            aux = CosteGlobal(MinFloyd);

            if(aux < min)
            {
                min = aux;
                sol.DeimosV = C1[i]; sol.FobosV = C2[j];
            }
            AuxiliarGrecoland = Grecoland;
        }

    return sol;
}

tcoste CosteGlobal(const matriz<tcoste>& G)
{
    tcoste Total = 0;
    for(int i=0; i<G.dimension(); i++)
        for(int j=0; j<G.dimension(); j++)
            Total = suma(Total, G[i][j]);

    return Total;
}