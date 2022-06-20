#include "agen.h"

template <typename T>
int GradoAgen(const Agen<T>& A)
{
    return GradoAgen_Rec(A.raiz(), A);
}

template <typename T>
int GradoAgen_Rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int Grado = 0, Aux, Hijos = 0;
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            Hijos++;
            Aux = GradoAgen_Rec(n, A);
            if(Grado < Aux) Grado = Aux;
            n = A.hermDrcho(n);
        }
        if(Hijos > Grado) return Hijos;
        else return Grado;
    }
}