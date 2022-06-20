/*--------------------------------------------------------*/
/* alg_grafoMA.h                                          */
/*                                                        */
/* Algoritmos para grafos no ponderados representados     */
/* mediante matriz de adyacencia.                         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Funciones:

   matriz<bool> Warshall(const Grafo& G);
      Determina si hay un camino entre cada par de vértices
      del grafo G.
      Devuelve una matriz booleana A de tamaño n x n, tal que
      A[i][j] == true si existe al menos un camino entre
      el vértice i y el vértice j, y A[i][j] == false si no
      existe ningún camino entre los vértices i y j.

   Lista<Grafo::vertice> Profundidad(const Grafo& G, Grafo::vertice v);
   Lista<Grafo::vertice> Profundidad2(const Grafo& G, Grafo::vertice v);
      Devuelve la lista de vértices del grafo G en el orden dado
      por el recorrido en profundidad, comenzando en el vértice v.

   Lista<Grafo::vertice> Anchura(const Grafo& G, Grafo::vertice v);
      Devuelve la lista de vértices del grafo G en el orden dado
      por el recorrido en anchura, comenzando en el vértice v.

*/

#ifndef ALG_GRAFO_H
#define ALG_GRAFO_H
#include "grafoMA.h"   // grafo no ponderado
#include "matriz.h"    // requerido por Warshall
#include "listaenla.h" // requerido por recorridos


matriz<bool> Warshall(const Grafo& G);

matriz<bool> Warshall(const Grafo& G)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   matriz<bool> A(n);
   
   // Inicializar A con la matriz de adyacencia de G
   for (vertice i = 0; i <= n-1; i++) {
      A[i] = G[i];
      A[i][i] = true;
   }
   
   // Comprobar camino entre cada par de vértices i, j
   // a través de cada vértice k
   for (vertice k = 0; k <= n-1; k++)
      for (vertice i = 0; i <= n-1; i++)
         for (vertice j = 0; j <= n-1; j++)
            if (!A[i][j])
               A[i][j] = A[i][k] && A[k][j];
   return A;
}


/*----------------------------------------------------------------------------*/
/* Recorridos de grafos no ponderados                                         */
/*----------------------------------------------------------------------------*/

Lista<Grafo::vertice> Profundidad(const Grafo& G, Grafo::vertice v);

Lista<Grafo::vertice> Profundidad2(const Grafo& G, Grafo::vertice v);

Lista<Grafo::vertice> Anchura(const Grafo& G, Grafo::vertice v);

#endif   // ALG_GRAFO_H
