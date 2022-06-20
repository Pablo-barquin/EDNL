#include "Abin.h"

template <typename T>
int ContarNodos(Abin<T> A)
{
    // La función debe funcionar PERFECTAMENTE para el NODO_NULO. Este if sobra porque la función sigue yendo bien sin el.
    // if(A.arbolVacio())
    //     return 0;
    // else ContarNodos_Rec(A, A.raiz());
    return ContarNodos_Rec(A, A.raiz());
}

template <typename T>
int ContarNodos_Rec(Abin<T> A, typename Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;

    else return 1 + ContarNodos_Rec(A, A.hijoIzqdo(n)) + ContarNodos_Rec(A, A.hijoDrcho(n));
}