#include "Abin.h"
#include <string>

using namespace std;

double MathAbin(const Abin<string>& A);
double MathAbin_Rec(typename Abin<string>::nodo n, const Abin<string>& A);

double MathAbin(const Abin<string>& A)
{
    if(A.arbolVacio())
        return 0;
    else return MathAbin_Rec(A.raiz(), A);
}

double MathAbin_Rec(typename Abin<string>::nodo n, const Abin<string>& A)
{
    typename Abin<string>::nodo nulo;
    nulo = Abin<string>::NODO_NULO;
    
    if(A.hijoIzqdo(n) == nulo && A.hijoDrcho(n) == nulo)
            return stod(A.elemento(n)); //Transforma cadena a double
    else 
    {
        if(A.elemento(n) == "+")
            return MathAbin_Rec(A.hijoIzqdo(n), A) + MathAbin_Rec(A.hijoDrcho(n), A); 
        else if(A.elemento(n) == "-")
            return MathAbin_Rec(A.hijoIzqdo(n), A) - MathAbin_Rec(A.hijoDrcho(n), A); 
        else if(A.elemento(n) == "*")
            return MathAbin_Rec(A.hijoIzqdo(n), A) * MathAbin_Rec(A.hijoDrcho(n), A); 
        else if(A.elemento(n) == "/")
            return MathAbin_Rec(A.hijoIzqdo(n), A) / MathAbin_Rec(A.hijoDrcho(n), A); 
    }
}