#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

using namespace std;

typedef unsigned int tCoste;


template <typename tCoste>
matriz<tCoste> FloydMod(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P);

template <typename T>
bool esAciclico(const matriz<T>& G);

int main()
{
    GrafoP<tCoste> G("Grafos/GrafoAcíclico2.txt");

    cout << G << endl;

    matriz<GrafoP<tCoste>::vertice> P;
    matriz<tCoste> MFloyd = FloydMod(G, P);

    cout << MFloyd;

    if(esAciclico(MFloyd))
        cout << "\nEste grafo es Acíclico";
    else cout << "\nEste grafo no es Acíclico";

}

template <typename tCoste>
matriz<tCoste> FloydMod(const GrafoP<tCoste>& G,
                     matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos

   // Iniciar A y P con caminos directos entre cada par de vértices.
   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];  // copia costes del grafo
      A[i][i] = GrafoP<tCoste>::INFINITO;
      P[i] = vector<vertice>(n, i);   // caminos directos
   }
   // Calcular costes mínimos y caminos correspondientes
   // entre cualquier par de vértices i, j
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++) {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if (ikj < A[i][j]) {
               A[i][j] = ikj;
               P[i][j] = k;
            }
         }
   return A;
}

template <typename T>
bool esAciclico(const matriz<T>& G)
{
    size_t i=0;
    while(i<G.dimension())
    {
        if(G[i][i] != GrafoP<T>::INFINITO)
            return false;
        else i++;
    }

    return true;
}