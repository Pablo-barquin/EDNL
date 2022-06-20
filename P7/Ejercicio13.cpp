#include "Util/alg_grafoPMC.h"
#include "Util/alg_grafo_E-S.h"

typedef unsigned int tcoste;
using namespace std;

struct Puente
{
    GrafoP<tcoste>::vertice v, w;
};

struct Solucion
{
    Puente P1, P2;
};

Solucion ConstruirPuentes(const GrafoP<tcoste>& I1, const GrafoP<tcoste>& I2, const GrafoP<tcoste>& I3, vector<GrafoP<tcoste>::vertice> C1, vector<GrafoP<tcoste>::vertice> C2, vector<GrafoP<tcoste>::vertice> C3);
tcoste CosteGlobal(const matriz<tcoste>& G);

int main()
{
    GrafoP<tcoste> I1("Grafos/GrafoEj12 Fobos.txt");
    GrafoP<tcoste> I2("Grafos/GrafoEj12 Deimos.txt");
    GrafoP<tcoste> I3("Grafos/GrafoEj13 Costa.txt");

    vector<GrafoP<tcoste>::vertice> C1{0,1,3,4}, C2{0,1,2}, C3{0,2};

    Solucion Final = ConstruirPuentes(I1, I2, I3, C1, C2, C3);
    
    cout << "Los puentes que obtienen el minimo costa global es: " << endl;
    cout << "Puente 1: Ciudad " << Final.P1.v << " (Fobos) -- Ciudad " << Final.P1.w << " (Deimos)" << endl; 
    cout << "Puente 1: Ciudad " << Final.P2.v << " (Fobos) -- Ciudad " << Final.P2.w << " (Costa)" << endl; 
}

Solucion ConstruirPuentes(const GrafoP<tcoste>& I1, const GrafoP<tcoste>& I2, const GrafoP<tcoste>& I3, vector<GrafoP<tcoste>::vertice> C1, vector<GrafoP<tcoste>::vertice> C2, vector<GrafoP<tcoste>::vertice> C3)
{
    // Unimos todos los grafos en uno completo
    int N1 = I1.numVert(), N2 = I2.numVert(), N3 = I3.numVert();
    GrafoP<tcoste> Huries(N1+N2+N3);

    // Rellenamos el grafo con los costes que tenemos
    for(int i=0; i<Huries.numVert(); i++)
        for(int j=0; j<Huries.numVert(); j++)
            if(i < N1 && j < N1)    // Añadimos los costes de la Isla 1
                Huries[i][j] = I1[i][j];
            else if(i >= N1 && i < N1+N2 && j >= N1 && j < N1+N2)   // Añadimos los costes de la Isla 2
                Huries[i][j] = I2[i-N1][j-N1];
            else if(i >= N1+N2 && j >= N1+N2)   // Añadimos los costes de la Isla 3
                Huries[i][j] = I3[i-(N1+N2)][j-(N1+N2)];

    // Vamos a buscar los puentes que minimicen el coste y unan las 3 islas
    Solucion sol;
    matriz<tcoste> MFloyd;
    matriz<GrafoP<tcoste>::vertice> P;
    GrafoP<tcoste> AuxiliarHuries = Huries;
    tcoste min = GrafoP<tcoste>::INFINITO, aux; 
    
    for(int i=0; i<C1.size(); i++)
        for(int j=0; j<C2.size(); j++)
            for(int k=0; k<C3.size(); k++)
            {
                // Conectamos 1 puente
                AuxiliarHuries[C1[i]][C2[j]+N1] = 0;
                AuxiliarHuries[C2[j]+N1][C1[i]] = 0;
                
                // Conectamos el otro puente
                AuxiliarHuries[C1[i]][C3[k]+N1+N2] = 0;
                AuxiliarHuries[C3[k]+N1+N2][C1[i]] = 0;

                MFloyd = Floyd(AuxiliarHuries, P);
                aux = CosteGlobal(MFloyd);
                if(aux < min)
                {
                    min = aux;
                    sol.P1.v = C1[i]; sol.P1.w = C2[j];
                    sol.P2.v = C1[i]; sol.P2.w = C3[k];
                }

                AuxiliarHuries = Huries;
            }

    return sol;
}

tcoste CosteGlobal(const matriz<tcoste>& G)
{
    tcoste Total = 0;
    for(int i=0; i<G.dimension(); i++)
        for(int j=0; j<G.dimension(); j++)
            Total = suma(Total, G[i][j]);

    return Total;
}