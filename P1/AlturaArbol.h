#include "Abin.h"
#include "cstdlib"

template <typename T>
int AlturaArbol(Abin<T> A)
{
    if(A.arbolVacio())
        return 0;
    else return AlturaArbol_Rec(A, A.raiz());
}

template <typename T>
int AlturaArbol_Rec(Abin<T> A, typename Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return -1;
    
    else return 1 + std::max(AlturaArbol_Rec(A, A.hijoIzqdo(n)), AlturaArbol_Rec(A, A.hijoDrcho(n)));
    
    // Esto esta bien, pero es otra forma de hacerlo sin usar std::max
    // else
    // {    
        
    //     int Izq, Der;

    //     Izq = AlturaArbol_Rec(A, A.hijoIzqdo(n));
    //     Der = AlturaArbol_Rec(A, A.hijoDrcho(n));

    //     if(Izq > Der)
    //         return 1 + Izq;
    //     else return 1 + Der;
    // }
}