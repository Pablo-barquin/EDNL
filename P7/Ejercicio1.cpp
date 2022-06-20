#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"

typedef unsigned int tcoste;
using namespace std;

template <typename tCoste>
matriz<tCoste> FloydMod(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoAcíclico2.txt");

    cout << G << endl;

    matriz<GrafoP<tcoste>::vertice> P;
    matriz<tcoste> MFloydMax = FloydMod(G, P);

    cout << MFloydMax;

    typedef typename GrafoP<tcoste>::vertice vertice;
    vertice origen, destino;
    tcoste max = 0;

    for(vertice i=0; i<G.numVert(); i++)
    {
        for(vertice j=0; j<G.numVert(); j++)
        {
            if(MFloydMax[i][j] > max && MFloydMax[i][j] != GrafoP<tcoste>::INFINITO)
            {
                max = MFloydMax[i][j];
                origen = i;
                destino = j;
            }
        }
    }

    cout << "Mayor coste: " << max << endl;
    cout << "Vertice Origen: " << origen << endl;
    cout << "Vertice Destino: " << destino << endl;
}

template <typename tCoste>
matriz<tCoste> FloydMod(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos

   // Iniciar A y P con caminos directos entre cada par de vértices.
   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];                    // copia costes del grafo
      A[i][i] = 0;                    // diagonal a 0
      P[i] = vector<vertice>(n, i);   // caminos directos
   }
   // Calcular costes mínimos y caminos correspondientes
   // entre cualquier par de vértices i, j
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++) {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if(A[i][j] == GrafoP<tCoste>::INFINITO){
               A[i][j] = ikj;
               P[i][j] = k;
            }
            else if(ikj > A[i][j] && ikj != GrafoP<tCoste>::INFINITO) {
               A[i][j] = ikj;
               P[i][j] = k;
            }
         }
   return A;
}