#include "Abin.h"
#include "abin_E-S.h"
#include "MathAbin.h"
#include "NietosAbin.h"
#include "NostalgicosAbin.h"

using namespace std;

typedef string tElto;
const tElto fin = "#"; // Fin de lectura. 

int main()
{
    Abin<tElto> A;

    ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    // rellenarAbin(A, fin); // Desde std::cin
    // ofstream fs("Nietos.dat"); // Abrir fichero de salida.
    // imprimirAbin(fs, A, fin); // En fichero.
    // fs.close();
    cout << "\n*** Árbol A guardado en fichero abin.dat ***\n"; 
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); 

    cout << "El numero de nodos con 3 nietos es: " << NietosAbin(A) << endl;
    cout << "El numero de nodos nostalgicos es: " << NostalgicosAbin(A) << endl;
    cout << "El resultado es: " << MathAbin(A) << endl;
}