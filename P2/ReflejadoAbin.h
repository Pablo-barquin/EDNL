#include "Abin.h"

template <typename T>
Abin<T> ReflejadoAbin(const Abin<T>& A)
{
    Abin<T> B;
    if(A.arbolVacio())
        return B;
    else
    {
        B.insertarRaiz(A.elemento(A.raiz()));
        ReflejadoAbin_Rec(A.raiz(), B.raiz(), A, B);
        return B;
    }
}

template <typename T>
void ReflejadoAbin_Rec(typename Abin<T>::nodo na, typename Abin<T>::nodo nb, const Abin<T>& A, Abin<T>& B)
{
    if(A.hijoIzqdo(na) != Abin<T>::NODO_NULO)
    {
        B.insertarHijoDrcho(nb, A.elemento(A.hijoIzqdo(na)));
        ReflejadoAbin_Rec(A.hijoIzqdo(na), B.hijoDrcho(nb), A, B);
    }
    if(A.hijoDrcho(na) != Abin<T>::NODO_NULO)
    {
        B.insertarHijoIzqdo(nb, A.elemento(A.hijoDrcho(na)));
        ReflejadoAbin_Rec(A.hijoDrcho(na), B.hijoIzqdo(nb), A, B);
    }
}