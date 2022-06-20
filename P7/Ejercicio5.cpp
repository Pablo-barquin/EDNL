#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"

typedef unsigned int tcoste;
using namespace std;

enum Alergico{Avion, Tren, Carretera};  // Alergias posibles del viajero

vector<bool> ComprobarCiudades(const GrafoP<tcoste>& Carretera, const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Avion, tcoste Dinero, enum Alergico, GrafoP<tcoste>::vertice origen);
GrafoP<tcoste> CrearMatriz(const GrafoP<tcoste>& G1, const GrafoP<tcoste>& G2);

int main()
{
    GrafoP<tcoste> Carretera("Grafos/GrafoConexo Avion.txt");
    GrafoP<tcoste> Avion("Grafos/GrafoConexo Carretera.txt");
    GrafoP<tcoste> Tren("Grafos/GrafoConexo Tren.txt");

    tcoste Dinero = 30;
    Alergico Malo = Alergico::Carretera;
    GrafoP<tcoste>::vertice origen = 0;

    vector<bool> CiudadesPosibles = ComprobarCiudades(Carretera, Tren, Avion, Dinero, Malo, origen);

    for(int i=0; i<CiudadesPosibles.size(); i++)
        cout << CiudadesPosibles[i] << "  ";
}

vector<bool> ComprobarCiudades(const GrafoP<tcoste>& Carretera, const GrafoP<tcoste>& Tren, const GrafoP<tcoste>& Avion, tcoste Dinero, Alergico Enfermedad, GrafoP<tcoste>::vertice origen)
{   
    // Creamos un nuevo grafo, con los costes directos mas pequeños entre los dos medios de transporte que pueda usar el viajero
    GrafoP<tcoste> GCombinada(Carretera.numVert());
    switch(Enfermedad)
    {
        case Alergico::Avion: GCombinada = CrearMatriz(Carretera, Tren); break;
        case Alergico::Carretera: GCombinada = CrearMatriz(Tren, Avion); break;
        case Alergico::Tren: GCombinada = CrearMatriz(Avion, Carretera); break;
    }

    // Realizamos Dijsktra para obtener los costes minimos de ir de la ciudad origen al resto de ciudades
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> Origen_Ciudad = Dijkstra(GCombinada, origen, P);

    // Creamos el vector de bool, que indicara si puede visitar la ciudad con el dinero que tiene o no
    vector<bool> PuedeIr(Origen_Ciudad.size(), false);

    // Si el coste minimo de ir a la ciudad es mas barato que el dinero que tiene, lo colocamos como true en el vector de bool
    for(int i=0; i<Origen_Ciudad.size(); i++)
        if(Origen_Ciudad[i] < Dinero)
            PuedeIr[i] = true;

    return PuedeIr;
}

GrafoP<tcoste> CrearMatriz(const GrafoP<tcoste>& G1, const GrafoP<tcoste>& G2)
{
    GrafoP<tcoste> M(G1.numVert());

    for(int i=0; i<G1.numVert(); i++)
        for(int j=0; j<G2.numVert(); j++)
            if(G1[i][j] > G2[i][j])
                M[i][j] = G2[i][j];
            else
                M[i][j] = G1[i][j];
            
    return M;
}