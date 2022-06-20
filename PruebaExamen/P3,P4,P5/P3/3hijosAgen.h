#include "agen.h"

template <typename T>
int Hijos3Agen(const Agen<T>& A)
{
    return Hijos3Agen_Rec(A.raiz(), A);
}

template <typename T>
int Hijos3Agen_Rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int cont = 0, nodos = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            cont++;
            nodos += Hijos3Agen_Rec(hijo, A);
            hijo = A.hermDrcho(hijo);
        }

        if(cont == 3) return 1 + nodos;
        else return 0 + nodos;
    }
}