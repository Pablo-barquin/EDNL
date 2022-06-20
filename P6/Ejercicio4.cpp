#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tCoste;
using namespace std;

GrafoP<tCoste> ZuelandiaEstado(GrafoP<tCoste> G, vector<bool> Ciudades, matriz<bool> Carreteras, typename GrafoP<tCoste>::vertice Capital);
void ActualizarCiudades(GrafoP<tCoste>& G, vector<bool> Ciudades);
void ActualizarCarreteras(GrafoP<tCoste>& G, matriz<bool> Carreteras);

int main()
{
    GrafoP<tCoste> MZuelandia("Grafos/Grafo10.txt");    // Costes en paz de Zuelandia
    vector<bool> CiudadesTomadas(MZuelandia.numVert(), false);  // Ciudades tomadas por los rebeldes
    matriz<bool> CarreterasTomadas(10);     // Carreteras tomadas por los rebeldes
    typename GrafoP<tCoste>::vertice Capital = 4;    // Capital de Zuelandia

    // Simulamos ciudades tomadas
    CiudadesTomadas[7] = true;
    CiudadesTomadas[2] = true;

    // Simulamos carreteras tomadas
    CarreterasTomadas[4][5] = true;
    CarreterasTomadas[5][4] = true;


    GrafoP<tCoste> MZuelandiaFinal = ZuelandiaEstado(MZuelandia, CiudadesTomadas, CarreterasTomadas, Capital);

    cout << MZuelandiaFinal;

}

GrafoP<tCoste> ZuelandiaEstado(GrafoP<tCoste> G, vector<bool> Ciudades, matriz<bool> Carreteras, typename GrafoP<tCoste>::vertice Capital)
{   
    ActualizarCiudades(G, Ciudades);    // Actualizamos la matriz de costes con las ciudades tomadas
    ActualizarCarreteras(G, Carreteras);    // Actualizamos la matriz de costes con las carreteras tomadas

    GrafoP<tCoste> NuevaZuelandia(G.numVert());     // Creamos un nuevo grafo donde ira la nueva matriz de costes con toda la informacion actualizada

    vector<GrafoP<tCoste>::vertice> P1;
    vector<tCoste> Capital_Destino = Dijkstra(G, Capital, P1);  // Costes desde la capital a todos los destinos

    vector<GrafoP<tCoste>::vertice> P2;
    vector<tCoste> Origen_Capital = DijkstraInv(G, Capital, P2);    // Costes desde todas las cidades a la capital

    // Creamos la nueva matriz de costes minimos pasando por la capital
    for(int i = 0; i < NuevaZuelandia.numVert(); i++)
    {
        for(int j = 0; j < NuevaZuelandia.numVert(); j++)
        {
            if(i != j)
                NuevaZuelandia[i][j] = suma(Origen_Capital[i], Capital_Destino[j]);
        }
    }

    // matriz<GrafoP<tCoste>::vertice> VertP;
    // matriz<tCoste> Mfloyd = Floyd(G, VertP);

    // cout << Mfloyd;

    return NuevaZuelandia;

}

void ActualizarCiudades(GrafoP<tCoste>& G, vector<bool> Ciudades)
{
    tCoste inf = GrafoP<tCoste>::INFINITO;
    for(int i = 0; i < G.numVert(); i++)
        if(Ciudades[i])
            for(int j = 0; j < G.numVert(); j++)
                G[i][j] = G[j][i] = inf;
}

void ActualizarCarreteras(GrafoP<tCoste>& G, matriz<bool> Carreteras)
{
    tCoste inf = GrafoP<tCoste>::INFINITO;
    for(int i = 0; i < G.numVert(); i++)
        for(int j = 0; j < G.numVert(); j++)
            if(Carreteras[i][j])
                G[i][j] = inf;
}

