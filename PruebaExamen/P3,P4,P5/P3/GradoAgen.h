#include "agen.h"

template <typename T>
int GradoAgen(const Agen<T>& A)
{
    return GradoAgen_Rec(A.raiz(), A);
}

template <typename T>
int GradoAgen_Rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int nhijos = 0, grado = 0, aux;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            nhijos++;
            aux = GradoAgen_Rec(hijo, A);
            if(aux > grado) grado = aux;
            hijo = A.hermDrcho(hijo);
        }

        if(nhijos > grado) return nhijos;
        else return grado;
    }
}