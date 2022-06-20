#include "Abb_E_S.h"
#include "PodaAbb.h"
#include "Operaciones.h"

using namespace std;
typedef int tElto;
const tElto fin = 0; // fin de lectura

template <typename T>
using Conjunto = Abb<T>;

int main()
{
    Conjunto<tElto> A, B, C;

    cout << "\n*** Lectura de árbol A de data.dat ***\n";
    ifstream fe("data.dat"); // Abrir fichero de entrada.
    insertarAbb(fe, A);     // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol A ***\n";
    mostrarAbb(A); // En std::cout

    cout << "\n*** Lectura de árbol A desde teclado ***\n";
    insertarAbb(B, fin);     // Desde fichero.
    cout << "\n*** Mostrar árbol B ***\n";
    mostrarAbb(B); // En std::cout

    // cout << "\n*** Equilibramos Arbol ***\n";
    // EquilibrarAbb(A);

    // cout << "\n*** Podamos el Arbol ***\n";
    // PodaAbb(A, 5);

    // cout << "\n*** Mostrar árbol A ***\n";
    // mostrarAbb(A); // En std::cout

    // C = Union(A, B);
    // cout << "\n*** Mostrar árbol C ***\n";
    // mostrarAbb(C);
}