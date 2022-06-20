#include "agen.h"

template <typename T>
int Nietos3Agen(const Agen<T>& A)
{
    return Nietos3Agen_Rec(A.raiz(), A);
}

template <typename T>
int Nietos3Agen_Rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int nietos = 0, nodos = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            nietos += NumNodos(hijo, A);
            nodos += Nietos3Agen_Rec(hijo, A);
            hijo = A.hermDrcho(hijo);
        }

        if(nietos == 3) return 1 + nodos;
        else return 0 + nodos;
    }
}

template <typename T>
int NumNodos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int hijos = 0;
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            hijos++;
            n = A.hermDrcho(n);
        }

        return hijos;
    }
}