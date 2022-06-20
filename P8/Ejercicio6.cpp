#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef int tcoste;
using namespace std;

struct Canal
{
    GrafoP<tcoste>::vertice origen, destino;
};

struct Solucion
{
    Canal Canal;
    tcoste Longitud;
    tcoste Caudal;
};

vector<Solucion> CaudalesValle(const GrafoP<tcoste> G, const GrafoP<tcoste> G_Caudal, int SubvencionCaudal, tcoste KmCanal);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoEj4.txt");
    GrafoP<tcoste> G_Caudal("Grafos/GrafoEj6 Caudal.txt");
    int Subvencion = 2;
    tcoste Kmcanal = 10;

    vector<Solucion> Sol = CaudalesValle(G, G_Caudal, Subvencion, Kmcanal);

    cout << "Los canales a realizar son los siguientes: " << endl;
    for(int i=0; i<Sol.size(); i++)
    {
        cout << "Conexion Canal:" << endl;
        cout << "  - Ciudad " << Sol[i].Canal.origen << " -- Ciudad " << Sol[i].Canal.destino << endl;
        cout << "Caudal del Canal: " << Sol[i].Caudal << endl;
        cout << "Longitud del Canal: " << Sol[i].Longitud << endl << endl;
    }
}

vector<Solucion> CaudalesValle(const GrafoP<tcoste> G, const GrafoP<tcoste> G_Caudal, int SubvencionCaudal, tcoste KmCanal)
{
    // Creamos una nueva matriz de costes, donde vamos a colocar los verdaderos costes
    int N = G.numVert();
    GrafoP<tcoste> NuevosCostes(N);

    // El coste nuevo de cada canal es: (KmCanal * G[i][j]) - (SubvencionCaudal * G_Caudal[i][j])
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            NuevosCostes[i][j] = (KmCanal * G[i][j]) - (SubvencionCaudal * G_Caudal[i][j]);

    cout << NuevosCostes;

    // Realizamos Prim o Kruskall para obtener la red de canales con coste minimo
    GrafoP<tcoste> Minimo = Prim(NuevosCostes);

    cout << Minimo;

    //Rellenamos la solucion final
    vector<Solucion> Final;
    for(int i=0; i<N; i++)
        for(int j=i; j<N; j++)
            if(Minimo[i][j] != GrafoP<tcoste>::INFINITO)
            {
                Solucion aux; 
                aux.Canal.origen = i; 
                aux.Canal.destino = j;
                aux.Caudal = G_Caudal[i][j];
                aux.Longitud = G[i][j];

                Final.push_back(aux);
            }

    return Final;
}