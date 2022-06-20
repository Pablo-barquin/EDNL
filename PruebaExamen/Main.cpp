#include "Abin.h"
#include "abin_E-S.h"
#include "ExamenMarzo.h"

using namespace std;

struct Proposicion
{
    bool simbolo;
    enum Conexion {Y, O, NO};
};

typedef int tElto;
const tElto fin = 0; // Fin de lectura. 

int main()
{
    Abin<tElto> A;

    ifstream fe("Valores2.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    // rellenarAbin(A, fin); // Desde std::cin
    // ofstream fs("Valores2.dat"); // Abrir fichero de salida.
    // imprimirAbin(fs, A, fin); // En fichero.
    // fs.close();

    cout << "\n*** Árbol A guardado en fichero abin.dat ***\n"; 
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); 

    cout << "El numero de hermanos reflejados es: " << ReflejadosAbin(A) << endl;
    
    // cout << "El valor de verdad es: "; 
    // if(ProposicionAbin(A)) cout << "True" << endl;
    // else cout << "False" << endl;
}