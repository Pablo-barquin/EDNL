#include <iostream>
#include <fstream>
#include "agen.h"
#include "agen_E-S.h"
#include "GradoAgen.h"
#include "ProfundidadAgen.h"
#include "DesequilibrioAgen.h"
#include "PodaAgen.h"
#include "3hijosAgen.h"
#include "3nietosAgen.h"

using namespace std;
typedef int tElto;
const tElto fin = 0; // fin de lectura

int main()
{
    Agen<tElto> A, B;
    
    // cout << "*** Lectura del árbol A ***\n";
    // rellenarAgen(A, fin);     // Desde std::cin
    // ofstream fs("Numeros3.dat");  // Abrir fichero de salida.
    // imprimirAgen(fs, A, fin); // En fichero.
    // fs.close();
    // cout << "\n*** Árbol A guardado en fichero agen.dat ***\n";
    
    cout << "\n*** Lectura de árbol B de agen.dat ***\n";
    ifstream fe("Numeros2.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);     // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol B ***\n";
    imprimirAgen(A); // En std::cout

    cout << "\nEl grado de este Agen es: " << GradoAgen(A) << endl;
    cout << "La profundidad del nodo es: " << ProfundidadAgen(A.hijoIzqdo(A.raiz()), A) << endl;
    cout << "La altura de este Agen es: " << DesequilibrioAgen(A) << endl;
    cout << "El numero de nodos con 3 hijos es: " << Hijos3Agen(A) << endl;
    cout << "El numero de nodos con 3 nietos es: " << Nietos3Agen(A) << endl;

    // PodaAgen(11, A);

    // cout << "Arbol al realizar poda: " << endl;
    // imprimirAgen(A);
    
}