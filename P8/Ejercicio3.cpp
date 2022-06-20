#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoEjemplo Ej3.txt");

    GrafoP<tcoste> G_Min = Prim(G);
    GrafoP<tcoste> G_Max = PrimMax(G);

    cout << G_Max;
}