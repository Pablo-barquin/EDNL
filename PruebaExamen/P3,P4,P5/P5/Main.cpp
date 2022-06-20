#include "TiposArboles/Abin.h"
#include "TiposArboles/agen.h"
// #include "TiposArboles/abin_E-S.h"
#include "TiposArboles/agen_E-S.h"
#include "Ejercicio1.h"
#include "Ejercicio4.h"

typedef int tElto;
const tElto fin = 0; // Fin de lectura. 

using namespace std;

int main()
{
    Agen<tElto> A;

    // cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    // ifstream fe("Datos/Numeros.dat"); // Abrir fichero de entrada.
    // rellenarAbin(fe, A); // Desde fichero.
    // fe.close();

    // rellenarAbin(A, fin); // Desde std::cin
    // ofstream fs("Numeros.dat"); // Abrir fichero de salida.
    // imprimirAbin(fs, A, fin); // En fichero.
    // fs.close();

    // cout << "\n*** Mostrar árbol binario A ***\n";
    // imprimirAbin(A);

    // EliminarElementoAbin(1, A);
    // cout << "\n*** Mostrar árbol binario A eliminando elemento ***\n";
    // imprimirAbin(A);

    // cout << "*** Lectura del árbol A ***\n";
    // rellenarAgen(A, fin);     // Desde std::cin
    // ofstream fs("Datos/agen.dat");  // Abrir fichero de salida.
    // imprimirAgen(fs, A, fin); // En fichero.
    // fs.close();
    // cout << "\n*** Árbol A guardado en fichero agen.dat ***\n";

    cout << "\n*** Lectura de árbol B de agen.dat ***\n";
    ifstream fe("Datos/agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);     // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol B ***\n";
    imprimirAgen(A); // En std::cout

    cout << "El arbol es ternario: " << esTernarioAgen(A);

}