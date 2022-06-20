#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

struct Solucion
{
    vector<unsigned int> Cantidades;
    tcoste CosteFinal;
};

Solucion DistribuirStock(const GrafoP<tcoste>& G, GrafoP<tcoste>::vertice Origen, unsigned int &Cantidad, vector<unsigned int> Almacenamiento, vector<float> Subvencion);
vector<tcoste> AplicarSubvenciones(vector<tcoste> Costes, vector<float> Subvencion);

int main()
{
    GrafoP<tcoste> G("Grafos/GrafoConexo.txt");
    GrafoP<tcoste>::vertice Origen = 0;
    unsigned int Cantidad = 1000;
    vector<unsigned int> Almacen{0, 375, 280, 473, 80};
    vector<float> Subvencion{10, 30, 25, 5, 100};

    Solucion Final = DistribuirStock(G, Origen, Cantidad, Almacen, Subvencion);

    cout << "Cantidad Restante: " << Cantidad << endl;
    cout << "Coste Minimo Final: " << Final.CosteFinal << endl;
    cout << "Distribucion Usada: " << endl;
    for(int i=0; i<Final.Cantidades.size(); i++)
    {
        cout << "Almacen " << i << ": " << Final.Cantidades[i] << " Elementos guardados." << endl;
    }

}

Solucion DistribuirStock(const GrafoP<tcoste>& G, GrafoP<tcoste>::vertice Origen, unsigned int &Cantidad, vector<unsigned int> Almacenamiento, vector<float> Subvencion)
{
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> CostesMinimos = Dijkstra(G, Origen, P);  // Calculo los costes minimos por producto de las ciudades

    vector<tcoste> CostesSubvencionados = AplicarSubvenciones(CostesMinimos, Subvencion);   // Obtenemos los costes por producto con las subvenciones aplicadas

    vector<unsigned int> CantidadFinal(G.numVert(), 0); // Aquí, guardaremos la cantidad de productos que va en cada ciudad
    GrafoP<tcoste>::vertice v;
    tcoste min = GrafoP<tcoste>::INFINITO;
    int i = 0;
    while(Cantidad > 0 && i < CostesSubvencionados.size())  // Mientras tengamos cantidad restante y no hayamos recorrido todos los nodos posibles
    {
        for(int j=0; j<CostesSubvencionados.size(); j++)    // Encontramos la ciudad que tenga menor coste y siga teniendo almacenamiento
        {
            if(min > CostesSubvencionados[j] && Almacenamiento[j] > 0)
            {
                min = CostesSubvencionados[j];
                v = j;
            }
        }

        if(Cantidad > Almacenamiento[v])    // Actualizamos las cantidades de almacenamiento
        {
            CantidadFinal[v] = Almacenamiento[v];
            Cantidad -= Almacenamiento[v];
            Almacenamiento[v] = 0;
        }
        else                
        {
            CantidadFinal[v] = Cantidad;
            Almacenamiento[v] -= Cantidad;
            Cantidad = 0;
        }
        i++;
        min = GrafoP<tcoste>::INFINITO;
    }

    Solucion Entrega;
    Entrega.Cantidades = CantidadFinal;
    Entrega.CosteFinal = 0;

    for(int i=0; i<CantidadFinal.size(); i++)
        Entrega.CosteFinal += CantidadFinal[i]*CostesSubvencionados[i];

    return Entrega;
}

vector<tcoste> AplicarSubvenciones(vector<tcoste> Costes, vector<float> Subvencion)
{
    vector<tcoste> CosteSub;
    for(int i=0; i<Costes.size(); i++)
        CosteSub.push_back(Costes[i] - (Costes[i]*(Subvencion[i]/100)));    // Guardamos el coste con el descuento aplicado de la subvención

    return CosteSub;
}   

