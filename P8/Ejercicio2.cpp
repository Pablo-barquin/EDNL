#include "Util/alg_grafoMA.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"
#include "cmath"

typedef double tcoste;
using namespace std;

struct Ciudad
{
    double x,y;
};

struct Isla
{
    vector<GrafoP<tcoste>::vertice> Ciudades;
};

struct LineaAerea
{
    Grafo::vertice A, B;
};

vector<LineaAerea> Tombuctu2(vector<Ciudad> ListaCiudades, Grafo MA);
tcoste CostesDirectos(Ciudad A, Ciudad B);
vector<Ciudad> AnadirCiudades();
LineaAerea CalcularAeropuerto(Isla A, Isla B, vector<Ciudad> Lista);

int main()
{
    Grafo MA("Grafos/GrafoMA Ej1.txt");
    vector<Ciudad> Lista = AnadirCiudades();

    vector<LineaAerea> Sol = Tombuctu2(Lista, MA);

    cout << "Las lineas aereas a crear, son las siguientes: " << endl;
    for(int i=0; i<Sol.size(); i++)
        cout << "Ciudad " << Sol[i].A << " --- Ciudad " << Sol[i].B << endl;
}

vector<LineaAerea> Tombuctu2(vector<Ciudad> ListaCiudades, Grafo MA)
{
    // Vamos a descubrir la forma que tiene el archipielago
    int N = MA.numVert();
    vector<Isla> Distribucion;

    matriz<bool> TotalCaminos = Warshall(MA);

    vector<bool> Visitados(N, false);
    for(int i=0; i<N; i++)
    {
        if(!Visitados[i])
        {
            Visitados[i] = true;
            Isla aux; aux.Ciudades.push_back(i);
            for(int j=0; j<N; j++)
            {
                if(TotalCaminos[i][j] && i != j)
                {
                    aux.Ciudades.push_back(j);
                    Visitados[j] = true;
                }
            }
            Distribucion.push_back(aux);
        }
    }

    vector<LineaAerea> Solucion;
    // Vamos a encontrar las lineas aereas que debemos crear
    for(int i=0; i<Distribucion.size(); i++)
        for(int j=i+1; j<Distribucion.size(); j++)
            Solucion.push_back(CalcularAeropuerto(Distribucion[i], Distribucion[j], ListaCiudades));

    return Solucion;
}

LineaAerea CalcularAeropuerto(Isla A, Isla B, vector<Ciudad> Lista)
{
    LineaAerea Solucion;
    tcoste min = GrafoP<tcoste>::INFINITO;
    Grafo::vertice v, w;

    for(int i=0; i<A.Ciudades.size(); i++)
        for(int j=0; j<B.Ciudades.size(); j++)
        {
            tcoste aux = CostesDirectos(Lista[A.Ciudades[i]], Lista[B.Ciudades[j]]);
            if(min > aux)
            {
                min = aux;
                Solucion.A = A.Ciudades[i];
                Solucion.B = B.Ciudades[j];
            }
        }

    return Solucion;
}

tcoste CostesDirectos(Ciudad A, Ciudad B)
{
    return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
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

/* 
    Crear Matriz de lineas aereas
    Comparamos v con w, miramos su representante, (Represante to isla), comprobamos que es de islas distintas
        - Miramos su distancia
        - Comprobamos en la matriz de lineas aereas si ese es el minimo, y modificamos esa matriz
    Devolvemos la matriz.
*/

/*
    Insertar en un APO origen-destino-coste
    Matriz de booleanos de Nislas-1
    Miro la cima del APO, si el par de vertices es de distintas islas, este es el MINIMO
    Coloco true en la matriz de booleanos y añado la solucion al vector
*/