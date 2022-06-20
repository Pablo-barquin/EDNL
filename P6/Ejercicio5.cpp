#include "Util/grafoPLA.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

template <typename tCoste> tCoste suma(tCoste x, tCoste y);

template <typename tCoste>
vector<tCoste> Dijkstra(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice origen, vector<typename GrafoP<tCoste>::vertice>& P);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoListaAdy.txt");

    cout << G;
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> V = Dijkstra(G, 1, P);
    
    cout << "Costes Minimos: ";
    for(int i=0; i<V.size(); i++)
        if(V.at(i) == GrafoP<tcoste>::INFINITO)
            cout << "-  ";
        else
            cout << V.at(i) << "  ";
}

template <typename tCoste>
vector<tCoste> Dijkstra(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice origen, vector<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v, w;
    const size_t n = G.numVert();
    vector<bool> S(n, false);                  // Conjunto de vértices vacío.
    vector<tCoste> D(n, GrafoP<tCoste>::INFINITO);     // Costes mínimos desde origen.

    typedef typename Lista<typename GrafoP<tCoste>::vertice_coste>::posicion posicion;
    // Iniciar D y P con caminos directos desde el vértice origen.
    for(posicion i = G.adyacentes(origen).primera(); i != G.adyacentes(origen).fin(); i = G.adyacentes(origen).siguiente(i))
        D.at(G.adyacentes(origen).elemento(i).v) = G.adyacentes(origen).elemento(i).c;
    D.at(origen) = 0;                             // Coste origen-origen es 0.
    P = vector<vertice>(n, origen);

    // Calcular caminos de coste mínimo hasta cada vértice.
    S[origen] = true;                          // Incluir vértice origen en S.
    for (size_t i = 1; i <= n-2; i++) {
        // Seleccionar vértice w no incluido en S
        // con menor coste desde origen.
        tCoste costeMin = GrafoP<tCoste>::INFINITO;
        for (v = 0; v < n; v++)
            if (!S[v] && D[v] <= costeMin) {
                costeMin = D[v];
                w = v;
            }
        S[w] = true;                          // Incluir vértice w en S.
        // Recalcular coste hasta cada v no incluido en S a través de w.
        for(posicion i = G.adyacentes(w).primera(); i != G.adyacentes(w).fin(); i = G.adyacentes(w).siguiente(i))
            if (!S[G.adyacentes(w).elemento(i).v]) {
                tCoste Owv = suma(D[w], G.adyacentes(w).elemento(i).c);
                if (Owv < D[G.adyacentes(w).elemento(i).v]) {
                    D[G.adyacentes(w).elemento(i).v] = Owv;
                    P[G.adyacentes(w).elemento(i).v] = w;
                }
            }
    }
    return D;
}

template <typename tCoste> tCoste suma(tCoste x, tCoste y)
{
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   if (x == INFINITO || y == INFINITO)
      return INFINITO;
   else
      return x + y;
}