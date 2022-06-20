#include "agen.h"


template <typename T>
void PodaAgen(int x, Agen<T>& A)
{
    PodaAgen_Rec(x, A.raiz(), A);
}

template <typename T>
bool PodaAgen_Rec(int x, typename Agen<T>::nodo n, Agen<T>& A)
{
    if(n != Agen<T>::NODO_NULO)
    {
        if(A.elemento(n) == x)
        {
            PodarAgen(n, A);
            if(A.hijoIzqdo(A.padre(n)) == n)
                A.eliminarHijoIzqdo(A.padre(n));
            else
            {
                typename Agen<T>::nodo hijo = A.padre(n);
                while(A.hermDrcho(hijo) != n)
                    hijo = A.hermDrcho(hijo);
                A.eliminarHermDrcho(hijo);
            }
            return true;
        }
        else
        {
            n = A.hijoIzqdo(n);
            bool flag = false;
            while(n != Agen<T>::NODO_NULO && flag == false)
            {
                flag = PodaAgen_Rec(x, n, A);
                n = A.hermDrcho(n);
            }
        }
    }
}

template <typename T>
void PodarAgen(typename Agen<T>::nodo n, Agen<T>& A)
{
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    while(hijo != Agen<T>::NODO_NULO)
    {
        PodarAgen(hijo, A);
        A.eliminarHijoIzqdo(n);
        hijo = A.hijoIzqdo(n);
    }
}