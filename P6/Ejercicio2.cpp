#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

using namespace std;

typedef unsigned int tCoste;

int main()
{
    GrafoP<tCoste> G("GrafoConexo.txt");

    cout << "El grafo es el siguiente:\n" << G;

    matriz<GrafoP<tCoste>::vertice> P(G.numVert());
    matriz<tCoste> MFloyd = Floyd(G, P);

    cout << "\nAl realizar Floyd, obtenemos la matriz de costes minimos:\n";
    cout << MFloyd;

    cout << "\nCalculamos el diametro del grafo\n";
    tCoste Diametro = GrafoP<tCoste>::INFINITO;
    for(int i=0; i<MFloyd.dimension(); i++)
    {
        // Primer Máximo
        int max1 = 0;
        typename GrafoP<tCoste>::vertice v1 = 0;
        for(int j=0; j<MFloyd.dimension(); j++)
        {
            if(MFloyd[i][j] != GrafoP<tCoste>::INFINITO && MFloyd[i][j] > max1)
            {
                max1 = MFloyd[i][j];
                v1 = j;
            }
        }

        // Segundo Máximo
        int max2 = 0;
        for(int j=0; j<MFloyd.dimension(); j++)
        {
            if(MFloyd[i][j] != GrafoP<tCoste>::INFINITO && MFloyd[i][j] > max2 && v1 != j)
                max2 = MFloyd[i][j];   
        }

        if(Diametro > max1+max2)
            Diametro = max1+max2;
    }

    cout << "El diametro del grafo es: " << Diametro;
}

// template <typename T>
// void ImprimirMatriz(matriz<T> M)
// {
//     cout << "    ";
//     for (int j = 0; j < M.dimension(); j++)
//         cout << std::setw(4) << j;
//     cout << std::endl;
//     for(int i=0; i<M.dimension(); i++)
//     {
//         cout << std::setw(4) << i;
//         for(int j=0; j<M[i].size(); j++)
//         {
//             if (M[i][j] == GrafoP<tCoste>::INFINITO || M[i][j] == 0)
//                 cout << std::setw(4) << "-";
//             else
//                 cout << std::setw(4) << M[i][j];
//         }
//         cout << "\n";
//     }   
// }