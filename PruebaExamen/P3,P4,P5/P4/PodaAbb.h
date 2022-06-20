#include "Abb.h"

template <typename T>
void PodaAbb(T x, Abb<T>& A)
{
    Abb<T> B = A.buscar(x);

    while(!B.vacio())
    {
        A.eliminar(B.elemento());
        B.eliminar(B.elemento());
    }
}

