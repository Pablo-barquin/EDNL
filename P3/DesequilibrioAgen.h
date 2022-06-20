#include "agen.h"
#include "algorithm"

template <typename T>
int DesequilibrioAgen(const Agen<T>& A)
{
    if(A.arbolVacio())
        return 0;
    else return AlturaAgen(A.raiz(), A) - MenorAltura(A.raiz(), A);
}

template <typename T>
int MenorAltura(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int Min;
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        typename Agen<T>::nodo Hijo = A.hijoIzqdo(n);
        while(Hijo != Agen<T>::NODO_NULO)
        {
            Min = AlturaAgen(Hijo, A);
            if(Min == 0)
                return 1;
            else Hijo = A.hermDrcho(Hijo);
        }
        
        return 1 + MenorAltura(A.hijoIzqdo(n), A);
    }
}

template <typename T>
int AlturaAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int Max = -1;
    if(n == Agen<T>::NODO_NULO)
        return -1;
    else
    {    
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            Max = std::max(Max, AlturaAgen(n, A));
            n = A.hermDrcho(n);   
        }
        return 1 + Max;
    }
}

