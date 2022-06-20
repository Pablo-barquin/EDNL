#include <iostream>
#include <fstream>
#include "agen.h"
#include "agen_E-S.h"
#include "GradoAgen.h"
#include "ProfundidadAgen.h"
#include "DesequilibrioAgen.h"
#include "PodaAgen.h"

using namespace std;
typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Agen<tElto> A, B;
    
    // cout << "*** Lectura del árbol A ***\n";
    // rellenarAgen(A, fin);     // Desde std::cin
    // ofstream fs("Numeros2.dat");  // Abrir fichero de salida.
    // imprimirAgen(fs, A, fin); // En fichero.
    // fs.close();
    // cout << "\n*** Árbol A guardado en fichero agen.dat ***\n";
    
    cout << "\n*** Lectura de árbol B de agen.dat ***\n";
    ifstream fe("agen2.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);     // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol B ***\n";
    imprimirAgen(A); // En std::cout
    
    cout << endl;
    cout << "El grado de este arbol es: " << GradoAgen(A) << endl;
    cout << "La altura del arbol es: " << AlturaAgen(A.raiz(), A) << endl;
    cout << "El desequilibrio del arbol es: " << DesequilibrioAgen(A) << endl;
    // cout << "Post-Poda del arbol" << endl;
    // PodaAgen(A, 7);
    // imprimirAgen(A);
}