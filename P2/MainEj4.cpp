#include "AbinAltura.h"
#include "ReflejadoAbin.h"

using namespace std;

typedef string tElto;
const tElto fin = "#"; // Fin de lectura. 

int main()
{
    AbinAltura<tElto> A(4, "-");

    // ifstream fe("Matematicas.dat"); // Abrir fichero de entrada.
    // rellenarAbin(fe, A); // Desde fichero.
    // fe.close();

    // rellenarAbin(A, fin); // Desde std::cin
    // ofstream fs("Matematicas2.dat"); // Abrir fichero de salida.
    // imprimirAbin(fs, A, fin); // En fichero.
    // fs.close();
    // cout << "\n*** Árbol A guardado en fichero abin.dat ***\n"; 
    // cout << "\n*** Mostrar árbol binario A ***\n";
    // imprimirAbin(A); 

    // cout << "El resultado de la operacion es: " << MathAbin(A) << endl;

    A.insertarRaiz("h");
    A.insertarHijoIzqdo(A.raiz(), "a");
    A.insertarHijoDrcho(A.raiz(), "m");
    A.insertarHijoDrcho(A.HijoIzqdo(A.raiz()), "b");
    A.insertarHijoIzqdo(A.HijoIzqdo(A.raiz()), "n");
    A.insertarHijoIzqdo(A.HijoDrcho(A.HijoIzqdo(A.raiz())), "l");
    A.insertarHijoDrcho(A.HijoDrcho(A.HijoIzqdo(A.raiz())), "d");
    A.insertarHijoIzqdo(A.HijoIzqdo(A.HijoDrcho(A.HijoIzqdo(A.raiz()))), "f");

}