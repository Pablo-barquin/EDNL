#include "Abin.h"
#include "abin_E-S.h"
#include "PseudoArbol.h"
#include "ContarNodos.h"
#include "AlturaArbol.h"

typedef char tElto;
const tElto fin = '#'; // Fin de lectura. 

using namespace std;

int main()
{
    Abin<tElto> A;

    // cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    // ifstream fe("abin.dat"); // Abrir fichero de entrada.
    // rellenarAbin(fe, A); // Desde fichero.
    // fe.close();

    rellenarAbin(A, fin); // Desde std::cin
    ofstream fs("Pseudo.dat"); // Abrir fichero de salida.
    imprimirAbin(fs, A, fin); // En fichero.
    fs.close();

    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); 

    cout << "El arbol es Pseudocompleto: " << PseudoArbol(A) << endl;
    cout << "La altura del arbol es: " << AlturaArbol(A) << endl;
    cout << "El numero de nodos es: " << ContarNodos(A) << endl;
    cout << "La profundidad del nodo es: " << A.Profundidad(A.raiz()) << endl;

}