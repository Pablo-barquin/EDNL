#include "Util/grafoMA.cpp"
#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"
#include "cmath"

typedef unsigned int tcoste;
using namespace std;

struct Ciudad
{
    int x, y;
};


Particion Tombuctu(vector<Ciudad> ListaCiudades, Grafo GA, matriz<tcoste>& Final);
tcoste CostesDirectos(Ciudad A, Ciudad B);
vector<Ciudad> AnadirCiudades();

int main()
{
    // GrafoP<tcoste> MA("Grafos/GrafoMA Ej1.txt");
    Grafo MA("Grafos/GrafoMA Ej1.txt");
    vector<Ciudad> Lista = AnadirCiudades();

    matriz<tcoste> Final(MA.numVert());
    Particion Islas = Tombuctu(Lista, MA, Final);
    cout << "Matriz de costes minimos entre cualquier ciudad" << endl;
    cout << Final << endl;

    vector<bool> Visitados(MA.numVert(), false);
    int k = 1;
    for(int i=0; i<MA.numVert(); i++)
    {
        int Representante = Islas.encontrar(i);
        if(!Visitados[i])
        {
            cout << "Isla " << k << endl;
            cout << " - Ciudad " << i << endl;
            Visitados[i] = true;
            for(int j=0; j<MA.numVert(); j++)
                if(Representante == Islas.encontrar(j) && !Visitados[j])
                {
                    cout << " - Ciudad " << j << endl;
                    Visitados[j] = true;
                }
            k++;
        }
    }



}

Particion Tombuctu(vector<Ciudad> ListaCiudades, Grafo GA, matriz<tcoste>& Final)
{
    int N = GA.numVert();
    // Creo un Grafo Ponderado de tamaño N nodos
    GrafoP<tcoste> CostesGA(N);

    // Creo una partición de tamaño N para obtener la distribucion de las islas
    Particion Islas(N);

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(GA[i][j])
            {
                int a = Islas.encontrar(i);
                int b = Islas.encontrar(j);
                if(a != b)
                    Islas.unir(a, b);
            }

    // Relleno Matriz de costes con los costes de la distancia directa entre dos ciudades
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(GA[i][j])
                CostesGA[i][j] = CostesDirectos(ListaCiudades[i], ListaCiudades[j]);
            else
                CostesGA[i][j] = GrafoP<tcoste>::INFINITO;

    // Obtengo la matriz de costes minimos entre dos ciudades cualesquiera
    matriz<GrafoP<tcoste>::vertice> P;
    Final = Floyd(CostesGA, P);

    return Islas;
}

tcoste CostesDirectos(Ciudad A, Ciudad B)
{
    return sqrt(pow(B.x - A.x, 2) + pow(B.y - B.y, 2));
}

vector<Ciudad> AnadirCiudades()
{
    Ciudad Aux;
    vector<Ciudad> Aux2;
    int i=0, fin;
    cout << "Escriba el numero de ciudades que vas a añadir: "; cin >> fin;
    while(i != fin)
    {
        cout << "Ciudad " << i << endl;
        cout << "Coordenada x: "; cin >> Aux.x; 
        cout << "Coordenada y: "; cin >> Aux.y;
        Aux2.push_back(Aux);
        cout << "\n";
        i++;
    };

    return Aux2; 
}