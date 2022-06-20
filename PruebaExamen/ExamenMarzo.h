#include "Abin.h"

template <typename T>
int ReflejadosAbin(const Abin<T>& A)
{
    if(A.arbolVacio())
        return 0;
    else return ReflejadosAbin_Rec(A.raiz(), A);
}

template <typename T>
int ReflejadosAbin_Rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else if(NodoVerde(n, A))
        return 2 + ReflejadosAbin_Rec(A.hijoIzqdo(n), A) + ReflejadosAbin_Rec(A.hijoDrcho(n), A);
    else return 0 + ReflejadosAbin_Rec(A.hijoIzqdo(n), A) + ReflejadosAbin_Rec(A.hijoDrcho(n), A);
}

template <typename T>
bool NodoVerde(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO || A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return false;
    else return NodoVerde_Rec(A.hijoIzqdo(n), A.hijoDrcho(n), A);
}

template <typename T>
bool NodoVerde_Rec(typename Abin<T>::nodo n1, typename Abin<T>::nodo n2, const Abin<T>& A)
{
    if(n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;
    else if(n1 == Abin<T>::NODO_NULO || n2 == Abin<T>::NODO_NULO)
        return false;
    else if(A.elemento(n1) == A.elemento(n2))
        return NodoVerde_Rec(A.hijoIzqdo(n1), A.hijoDrcho(n2), A) && NodoVerde_Rec(A.hijoDrcho(n1), A.hijoIzqdo(n2), A);
    else return false;
}