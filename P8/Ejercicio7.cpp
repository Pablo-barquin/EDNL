#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"
#include "cmath"

enum Isla{FOBOS, DEIMOS};

typedef unsigned int tcoste;
using namespace std;

struct Puente
{
    GrafoP<tcoste>::vertice v, w;
    tcoste Coste;
};

struct Ciudad
{
    int CoorX, CoorY;
    int N;
    Isla Tipo;
};

tcoste ViajeMinimoGrecoland(vector<Ciudad> C_Fobos, vector<Ciudad> C_Deimos, vector<bool> Costeras_Fobos, vector<bool> Costeras_Deimos, Ciudad Origen, Ciudad Destino);
void ReconstruirGrafo(GrafoP<tcoste>& G, vector<Ciudad> Lista);
tcoste CostesDirectos(Ciudad A, Ciudad B);
Puente EncontrarPuente(vector<Ciudad> Ciudades1, vector<Ciudad> Ciudades2, vector<bool> Lista1, vector<bool> Lista2);
vector<Ciudad> AnadirCiudadesF();
vector<Ciudad> AnadirCiudadesD();

int main()
{
    vector<Ciudad> Fobos = AnadirCiudadesF();
    vector<Ciudad> Deimos = AnadirCiudadesD();
    vector<bool> ListaCost1{false, true, true, false};
    vector<bool> ListaCost2{true, true, false, false, true};

    tcoste Fin = ViajeMinimoGrecoland(Fobos, Deimos, ListaCost1, ListaCost2, Fobos[3], Deimos[3]);
    cout << "El coste final es: " << Fin;
}

tcoste ViajeMinimoGrecoland(vector<Ciudad> C_Fobos, vector<Ciudad> C_Deimos, vector<bool> Costeras_Fobos, vector<bool> Costeras_Deimos, Ciudad Origen, Ciudad Destino)
{
    //Primero, resolvemos la reconstruccion de las carreteras de manera local en cada Isla
    int NF = C_Fobos.size(), ND = C_Deimos.size();
    GrafoP<tcoste> G_Fobos(NF), G_Deimos(ND);

    ReconstruirGrafo(G_Fobos, C_Fobos);
    ReconstruirGrafo(G_Deimos, C_Deimos);

    // Obtenemos el coste minimo de unir todas las carreteras de cada isla usando Prim o Kruskall
    GrafoP<tcoste> FobosMinimo = Prim(G_Fobos), DeimosMinimo = Prim(G_Deimos);

    // Vamos a encontrar el puente mas cercano entre las ciudades costeras
    Puente ConexionIsla = EncontrarPuente(C_Fobos, C_Deimos, Costeras_Fobos, Costeras_Deimos);

    // Sabiendo las tres soluciones de forma local, podemos obtener el resultado final
    GrafoP<tcoste> GrafoFinal(NF+ND);
    for(int i=0; i<GrafoFinal.numVert(); i++)
        for(int j=0; j<GrafoFinal.numVert(); j++)
            if(i < NF && j < NF)
                GrafoFinal[i][j] = FobosMinimo[i][j];
            else if(i >= NF && j >= NF)
                GrafoFinal[i][j] = DeimosMinimo[i-NF][j-NF];
    
    GrafoFinal[ConexionIsla.v][ConexionIsla.w] = GrafoFinal[ConexionIsla.w][ConexionIsla.v] = ConexionIsla.Coste;

    // Con el grafo montado, solo falta obtener el coste del camino
    vector<GrafoP<tcoste>::vertice> P;
    vector<tcoste> CosteCamino;
    if(Origen.Tipo == Isla::FOBOS)
        CosteCamino = Dijkstra(GrafoFinal, Origen.N, P);
    else
        CosteCamino = Dijkstra(GrafoFinal, Origen.N+NF, P);

    if(Destino.Tipo == Isla::FOBOS)
        return CosteCamino[Destino.N];
    else
        return CosteCamino[Destino.N + NF];
}

void ReconstruirGrafo(GrafoP<tcoste>& G, vector<Ciudad> Lista)
{
    for(int i=0; i<Lista.size(); i++)
    {
        Ciudad aux = Lista[i];
        for(int j=i; j<Lista.size(); j++)
        {
            Ciudad aux2 = Lista[j];
            if(aux.N == aux2.N)
                G[aux.N][aux2.N] = G[aux2.N][aux.N] = 0;
            else
                G[aux.N][aux2.N] = G[aux2.N][aux.N] = CostesDirectos(aux, aux2);
        }
    }
}

tcoste CostesDirectos(Ciudad A, Ciudad B)
{
    return sqrt(pow(B.CoorX - A.CoorX, 2) + (B.CoorY - A.CoorY, 2));
}

Puente EncontrarPuente(vector<Ciudad> Ciudades1, vector<Ciudad> Ciudades2, vector<bool> Lista1, vector<bool> Lista2)
{
    Puente sol;
    sol.Coste = GrafoP<tcoste>::INFINITO;
    for(int i=0; i<Ciudades1.size(); i++)
        if(Lista1[i])
        {
            for(int j=0; j<Ciudades2.size(); j++)
                if(Lista2[j])
                {
                    tcoste aux = CostesDirectos(Ciudades1[i], Ciudades2[i]);
                    if(sol.Coste > aux)
                    {
                        sol.Coste = aux;
                        sol.v = Ciudades1[i].N;
                        sol.w = Ciudades2[j].N + Ciudades1.size();
                    }
                }
        }

    return sol;
}

vector<Ciudad> AnadirCiudadesF()
{
    Ciudad Aux;
    vector<Ciudad> Aux2;
    int i=0, fin = 4;
    while(i != fin)
    {
        cout << "Ciudad " << i << " - FOBOS" << endl;
        cout << "Coordenada x: "; cin >> Aux.CoorX; 
        cout << "Coordenada y: "; cin >> Aux.CoorY;
        Aux.N = i;
        Aux.Tipo = Isla::FOBOS;
        Aux2.push_back(Aux);
        cout << "\n";
        i++;
    };

    return Aux2; 
}

vector<Ciudad> AnadirCiudadesD()
{
    Ciudad Aux;
    vector<Ciudad> Aux2;
    int i=0, fin = 5;
    while(i != fin)
    {
        cout << "Ciudad " << i << " - DEIMOS" << endl;
        cout << "Coordenada x: "; cin >> Aux.CoorX; 
        cout << "Coordenada y: "; cin >> Aux.CoorY;
        Aux.N = i;
        Aux.Tipo = Isla::DEIMOS;
        Aux2.push_back(Aux);
        cout << "\n";
        i++;
    };

    return Aux2; 
}