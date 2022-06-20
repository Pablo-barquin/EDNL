#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"
#include "iostream"

typedef unsigned int tcoste;
using namespace std;

struct Puentes
{
    GrafoP<tcoste>::vertice v, w;
};

matriz<tcoste> CosteMinimo(const GrafoP<tcoste>& Isla1, const GrafoP<tcoste>& Isla2, const GrafoP<tcoste>& Isla3, vector<Puentes> Conexiones);

int main()
{
    GrafoP<tcoste> I1("Grafos/GrafoEj11 Isla1.txt");
    GrafoP<tcoste> I2("Grafos/GrafoEj11 Isla2.txt");
    GrafoP<tcoste> I3("Grafos/GrafoEj11 Isla3.txt");

    vector<Puentes> Conexiones;
    Puentes P1, P2;
    P1.v = 0; P1.w = 3;
    P2.v = 6; P2.w = 7;

    Conexiones.push_back(P1); Conexiones.push_back(P2);

    matriz<tcoste> solucion = CosteMinimo(I1, I2, I3, Conexiones);

    cout << "La matriz de costes minimos entre las islas es: " << endl;
    cout << solucion;
}

matriz<tcoste> CosteMinimo(const GrafoP<tcoste>& Isla1, const GrafoP<tcoste>& Isla2, const GrafoP<tcoste>& Isla3, vector<Puentes> Conexiones)
{
    // Necesito una matriz que contenga a los 3 grafos -> N1+N2+N3 nodos
    int N1 = Isla1.numVert(), N2 = Isla2.numVert(), N3 = Isla3.numVert();
    GrafoP<tcoste> Zuelandia(N1+N2+N3);

    // Relleno el nuevo grafo con las conexiones que existen actualmente entre cada isla
    for(int i=0; i<Zuelandia.numVert(); i++)
        for(int j=0; j<Zuelandia.numVert(); j++)
        {
            if(i < N1 && j < N1)    // Rellenamos con los valores de la primera isla
                Zuelandia[i][j] = Isla1[i][j];
            else if(i >= N1 && i < N1+N2 && j >= N1 && j < N1+N2)   // Rellenamos con los valores de la segunda isla
                Zuelandia[i][j] = Isla2[i-N1][j-N1];
            else if(i >= N1+N2 && j >= N1+N2)   // Rellenamos con los valores de la tercera isla
                Zuelandia[i][j] = Isla3[i-(N1+N2)][j-(N1+N2)];
        }

    // Añadimos los puentes que hayan
    int it = 0;
    while(it < Conexiones.size())
    {
        Zuelandia[Conexiones[it].v][Conexiones[it].w] = 0;
        Zuelandia[Conexiones[it].w][Conexiones[it].v] = 0;
        it++;
    }

    matriz<GrafoP<tcoste>::vertice> P;
    matriz<tcoste> MFloyd = Floyd(Zuelandia, P);

    return MFloyd;
}
