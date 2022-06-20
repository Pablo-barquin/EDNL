#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

tcoste ViajeMinimo(const GrafoP<tcoste>&, const GrafoP<tcoste>&, vector<GrafoP<tcoste>::vertice>&, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice);
vector<GrafoP<tcoste>::vertice> CaminoRecorrido(GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice, vector<GrafoP<tcoste>::vertice>, vector<GrafoP<tcoste>::vertice>);

int main()
{
    GrafoP<tcoste> Tren("Grafos/GrafoEj7 Tren.txt");
    GrafoP<tcoste> Bus("Grafos/GrafoEj7 Bus.txt");
    vector<GrafoP<tcoste>::vertice> P;
    GrafoP<tcoste>::vertice Origen = 1, Destino = 9, Cambio1 = 4, Cambio2 = 3;

    tcoste CosteFinal = ViajeMinimo(Tren, Bus, P, Origen, Destino, Cambio1, Cambio2);

    cout << "El coste final es de: " << CosteFinal << endl;
    cout << "El recorrido es: " << endl;
    for(int i=0; i<P.size(); i++)
        cout << "Paso " << (i+1) <<": " << P[i] << endl;
}

tcoste ViajeMinimo(const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, vector<GrafoP<tcoste>::vertice>& Pfinal, GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino, GrafoP<tcoste>::vertice cambio1, GrafoP<tcoste>::vertice cambio2)
{
    // Calculo los costes minimos de origen-vertices y vertices-destino
    vector<GrafoP<tcoste>::vertice> P1;
    vector<tcoste> TrenMinimo = Dijkstra(Tren, origen, P1);

    vector<GrafoP<tcoste>::vertice> P2;
    vector<tcoste> BusMinimo = DijkstraInv(Bus, destino, P2);

    // Obtengo el coste minimo y el camino para llegar desde origen a destino
    tcoste cam1 = suma(TrenMinimo[cambio1], BusMinimo[cambio1]);
    tcoste cam2 = suma(TrenMinimo[cambio2], BusMinimo[cambio2]);

    tcoste final;
    if(cam1 < cam2)
    {
        final = cam1;
        Pfinal = CaminoRecorrido(origen, destino, cambio1, P1, P2);
    }
    else
    {
        final = cam2;
        Pfinal = CaminoRecorrido(origen, destino, cambio2, P1, P2);
    }

    return final;
}

vector<GrafoP<tcoste>::vertice> CaminoRecorrido(GrafoP<tcoste>::vertice origen, GrafoP<tcoste>::vertice destino, GrafoP<tcoste>::vertice cambio, vector<GrafoP<tcoste>::vertice> P1, vector<GrafoP<tcoste>::vertice> P2)
{
    vector<GrafoP<tcoste>::vertice> CaminoAux, Camino;
    GrafoP<tcoste>::vertice cambio2 = cambio;

    CaminoAux.push_back(cambio);
    do
    {
        CaminoAux.push_back(P2[cambio]);
        cambio = P2[cambio];
    }while (destino != cambio);

    while(CaminoAux.size() > 0)
    {
        Camino.push_back(CaminoAux[CaminoAux.size()-1]);
        CaminoAux.pop_back();
    }

    CaminoAux = Camino;
    Camino.clear();

    do
    {
        CaminoAux.push_back(P1[cambio2]);
        cambio2 = P1[cambio2];
    } while (cambio2 != origen);
    
    while(CaminoAux.size() > 0)
    {
        Camino.push_back(CaminoAux[CaminoAux.size()-1]);
        CaminoAux.pop_back();
    }
    
    return Camino;
}