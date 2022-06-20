#include "Abb_E_S.h"
// #include "PodaAbb.h"
// #include "EquilibrarAbb.h"
// #include "OperacionesAbb.h"

using namespace std;
typedef int tElto;
const tElto fin = 0; // fin de lectura

typedef Abb<tElto> Conjunto;

int main()
{
    Conjunto A, B, C;

    ifstream fe("data.dat"); // Abrir fichero de entrada.
    insertarAbb(fe, A);     // Desde fichero.
    fe.close();
    
    // cout << "\n*** Lectura de árbol A desde teclado ***\n";
    // insertarAbb(B, fin);     // Desde fichero.
    
    cout << "\n*** Mostrar árbol A ***\n";
    mostrarAbb(A); // En std::cout

    while(!A.drcho().vacio())
    {
        B = A.drcho();
        A = B;
    }

    cout << "El elemento mas a la derecha es: " << A.elemento();

    
    // cout << "\n*** Mostrar árbol B ***\n";
    // mostrarAbb(B); // En std::cout

    // cout << "\n*** Equilibramos Arbol ***\n";
    // EquilibrarAbb(B);

    // cout << "\n*** Podamos el Arbol ***\n";
    // PodaAbb(18, A);

    // cout << "\n*** Mostrar árbol B ***\n";
    // mostrarAbb(B); // En std::cout

    // C = Union(A, B);
    // cout << "\n*** Mostrar árbol C Equilibrado ***\n";
    // EquilibrarAbb(C);
    // mostrarAbb(C);
}