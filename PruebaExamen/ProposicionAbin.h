#include "Abin.h"

template <typename T>
bool ProposicionAbin(const Abin<T>& A)
{
    return ProposicionAbin_Rec(A.raiz(), A);
}

template <typename T>
bool ProposicionAbin_Rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO) //Hipotetico caso que el arbol este vacio
        return true;    
    else
    {
        if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)   //Nodo hoja = Verdadero o falso
        {
            return A.elemento(n).simbolo; 
        }
        else    //Comprobamos conexión lógica
        {
            if(A.elemento(n) == "Y") return (ProposicionAbin_Rec(A.hijoIzqdo(n), A) && ProposicionAbin_Rec(A.hijoDrcho(n), A));
            else if(A.elemento(n) == "O") return (ProposicionAbin_Rec(A.hijoIzqdo(n), A) || ProposicionAbin_Rec(A.hijoDrcho(n), A));
            else if(A.elemento(n) == "NO") return !ProposicionAbin_Rec(A.hijoIzqdo(n), A);
        }
    }
}