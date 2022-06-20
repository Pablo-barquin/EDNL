#include "agen.h"

template <typename T>
int DesequilibrioAgen(const Agen<T>& A)
{
    if(A.arbolVacio())
        return 0;
    else return abs(AlturaAgen(A.raiz(), A) - CaminoRamaCortaAgen(A.raiz(), A));
}

template <typename T>
int AlturaAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return -1;
    else
    {
        int max = -1, aux;
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            aux = AlturaAgen(n, A);
            if(aux > max) max = aux;
            n = A.hermDrcho(n);
        }

        return 1 + max;
    }
}

template <typename T>
int CaminoRamaCortaAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int minimo = AlturaAgen(n, A), aux;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            if(AlturaAgen(hijo, A) == 0)
                return 1;
            else aux = 1 + CaminoRamaCortaAgen(hijo, A);

            if(minimo > aux) minimo = aux;
            hijo = A.hermDrcho(hijo);
        }

        return minimo;
    }
}

