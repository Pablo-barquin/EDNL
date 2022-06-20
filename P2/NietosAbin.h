#include "Abin.h"

template <typename T>
int NietosAbin(const Abin<T>& A)
{
    return NietosAbin_Rec(A.raiz(), A);
}

template <typename T>
int NietosAbin_Rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;

    else if(ContarNodos(A.hijoIzqdo(n), A) + ContarNodos(A.hijoDrcho(n), A) == 3)
        return 1 + NietosAbin_Rec(A.hijoIzqdo(n), A) + NietosAbin_Rec(A.hijoDrcho(n), A);
    
    else return NietosAbin_Rec(A.hijoIzqdo(n), A) + NietosAbin_Rec(A.hijoDrcho(n), A);
}

template <typename T>
int ContarNodos(typename Abin<T>::nodo n, const Abin<T>& A)
{
    int nodos = 0;
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
            nodos++;
        if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)
            nodos++;
        return nodos;
    }
}