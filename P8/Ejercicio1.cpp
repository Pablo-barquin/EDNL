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

struct Isla
{
    vector<int> Ciudades;
};

struct Solucion
{
    matriz<tcoste> MatrizMinima;
    vector<Isla> Distribucion;
};

Solucion Tombuctu(vector<Ciudad> ListaCiudades, Grafo GA);
tcoste CostesDirectos(Ciudad A, Ciudad B);
vector<Ciudad> AnadirCiudades();

int main()
{
    // GrafoP<tcoste> MA("Grafos/GrafoMA Ej1.txt");
    Grafo MA("Grafos/GrafoMA Ej1.txt");
    vector<Ciudad> Lista = AnadirCiudades();

    Solucion Final = Tombuctu(Lista, MA);
    cout << "Matriz de costes minimos entre cualquier ciudad";
    cout << Final.MatrizMinima << endl;

    for(int i=0; i<Final.Distribucion.size(); i++)
    {
        cout << "Isla " << i << endl;
        for(int j=0; j<Final.Distribucion[i].Ciudades.size(); j++)
            cout << "\t - Ciudad " << Final.Distribucion[i].Ciudades[j] << endl;
    }
}

Solucion Tombuctu(vector<Ciudad> ListaCiudades, Grafo GA)
{
    int N = GA.numVert();
    // Creo un Grafo Ponderado de tamaño N nodos
    GrafoP<tcoste> CostesGA(N);

    // Relleno Matriz de costes con los costes de la distancia directa entre dos ciudades
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(GA[i][j])
                CostesGA[i][j] = CostesDirectos(ListaCiudades[i], ListaCiudades[j]);
            else
                CostesGA[i][j] = GrafoP<tcoste>::INFINITO;

    // Obtengo la matriz de costes minimos entre dos ciudades cualesquiera
    Solucion sol;
    matriz<GrafoP<tcoste>::vertice> P;
    sol.MatrizMinima = Floyd(CostesGA, P);


    // Obtengo la distribucion Final
    vector<bool> Visitadas(N, false);
    for(int i=0; i<N; i++)
    {
        if(!Visitadas[i])
        {
            Visitadas[i] = true;
            Isla Aux; Aux.Ciudades.push_back(i);
            for(int j=0; j<N; j++)
            {
                if(sol.MatrizMinima[i][j] != GrafoP<tcoste>::INFINITO && !Visitadas[j])
                {
                    Aux.Ciudades.push_back(j);
                    Visitadas[j] = true;
                }
            }
            sol.Distribucion.push_back(Aux);
        }
    }

    return sol;
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