#include "Abin.h"
#include <cstdlib>


template <typename T>
int DesequilibrioArbol(Abin<T> A)
{
    // if(A.arbolVacio())
    //     return 0;
    // else return DesequilibrioArbol_Rec(A, A.raiz());
    return DesequilibrioArbol_Rec(A, A.raiz());
}

template <typename T>
int DesequilibrioArbol_Rec(Abin<T> A, typename Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        int Max, Izq, Der;
        Max = std::max(DesequilibrioArbol_Rec(A, A.hijoIzqdo(n)), DesequilibrioArbol_Rec(A, A.hijoDrcho(n)));
        Izq = A.Altura(A.hijoIzqdo(n));
        Der = A.Altura(A.hijoDrcho(n));

        if(Max > std::abs(Izq - Der))
            return Max;
        else return std::abs(Izq - Der);

    }
}