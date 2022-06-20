#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

matriz<tcoste> TarifaMinimaViaje(const GrafoP<tcoste>&, const GrafoP<tcoste>&, GrafoP<tcoste>::vertice);
tcoste ValorMinimo(const matriz<tcoste>&, const matriz<tcoste>&, GrafoP<tcoste>::vertice, int, int);

int main()
{
    GrafoP<tcoste> Tren("Grafos/GrafoEj6 Tren.txt");
    GrafoP<tcoste> Bus("Grafos/GrafoEj6 Bus.txt");
    GrafoP<tcoste>::vertice CiudadTransbordo = 2;

    matriz<tcoste> MinimoValor = TarifaMinimaViaje(Tren, Bus, CiudadTransbordo);

    cout << MinimoValor;
}

matriz<tcoste> TarifaMinimaViaje(const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, GrafoP<tcoste>::vertice CiudadTransbordo)
{
    // Calculamos la matriz de costes minimos de viajar en tren y en bus
    matriz<GrafoP<tcoste>::vertice> P;
    matriz<tcoste> MinimoTren = Floyd(Tren, P);
    matriz<tcoste> MinimoBus = Floyd(Bus, P);

    // Creamos una nueva matriz donde asignaremos los valores minimos de viajar de una ciudad a otra entre bus, tren y los posibles transbordos bus-tren y tren-bus
    matriz<tcoste> TarifaMinima(Tren.numVert());

    for(int i=0; i<TarifaMinima.dimension(); i++)
        for(int j=0; j<TarifaMinima.dimension(); j++)
            TarifaMinima[i][j] = ValorMinimo(MinimoTren, MinimoBus, CiudadTransbordo, i, j);

    return TarifaMinima;
}

tcoste ValorMinimo(const matriz<tcoste>& M1, const matriz<tcoste>& M2, GrafoP<tcoste>::vertice CiudadTransbordo, int i, int j)
{
    // Calculamos los transbordos
    tcoste TransbordoM1_M2 = suma(M1[i][CiudadTransbordo], M2[CiudadTransbordo][j]);
    tcoste TransbordoM2_M1 = suma(M2[i][CiudadTransbordo], M1[CiudadTransbordo][j]);

    // Obtengo el minimo transbordo
    tcoste Transbordo = min(TransbordoM1_M2, TransbordoM2_M1);

    // Obtengo el minimo coste directo
    tcoste Directo = min(M1[i][j], M2[i][j]);

    // Devuelvo el valor minimo posible
    return min(Transbordo, Directo);
}