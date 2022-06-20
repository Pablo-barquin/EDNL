#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

tcoste TarifaMinima(const GrafoP<tcoste>&, const GrafoP<tcoste>&, GrafoP<tcoste>::vertice, GrafoP<tcoste>::vertice);

int main()
{
    GrafoP<tcoste> Tren("Grafos/GrafoEj7 Tren.txt");
    GrafoP<tcoste> Bus("Grafos/GrafoEj7 Bus.txt");

    GrafoP<tcoste>::vertice Origen = 0, Destino = 8;

    tcoste Tarifa = TarifaMinima(Tren, Bus, Origen, Destino);

    cout << "El coste mas barato del viaje es: " << Tarifa;
}

tcoste TarifaMinima(const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Bus, GrafoP<tcoste>::vertice Origen, GrafoP<tcoste>::vertice Destino)
{
    int N = Tren.numVert();
    vector<GrafoP<tcoste>::vertice> P;
    // Calculamos los costes minimos de ir en tren y en bus del origen al destino
    vector<tcoste> MinimoTrenOrigen = Dijkstra(Tren, Origen, P);
    vector<tcoste> MinimoBusOrigen = Dijkstra(Bus, Origen, P);

    // Esto son los costes de ir solamente en tren o solamente en bus
    tcoste SoloTren = MinimoTrenOrigen[Destino];
    tcoste SoloBus = MinimoBusOrigen[Destino];

    // Ahora calculamos el coste minimo de ir de cualquier vertice al destino solamente en bus o en tren
    vector<tcoste> MinimoTrenDestino = DijkstraInv(Tren, Destino, P);
    vector<tcoste> MinimoBusDestino = DijkstraInv(Bus, Destino, P);

    // Hallamos el coste minimo de empezar en tren y acabar en bus, y viceversa, realizando solo un transbordo en alguna ciudad
    tcoste Tren_Bus = GrafoP<tcoste>::INFINITO, Bus_Tren = GrafoP<tcoste>::INFINITO, OtD;
    int w;
    for(int i=0; i<N; i++)
    {
        OtD = suma(MinimoTrenOrigen[i], MinimoBusDestino[i]);
        if(Tren_Bus > OtD)
            Tren_Bus = OtD;
        
        OtD = suma(MinimoBusOrigen[i], MinimoTrenDestino[i]);
        if(Bus_Tren > OtD)
            Bus_Tren = OtD;
    }

    // Obtenemos el coste minimo
    tcoste MinimoDirecto = min(SoloBus, SoloTren);
    tcoste MinimoTransbordo = min(Tren_Bus, Bus_Tren);

    return min(MinimoDirecto, MinimoTransbordo);

}