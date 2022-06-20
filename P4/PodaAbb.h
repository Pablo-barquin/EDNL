#include "Abb.h"

template <typename T>
void PodaAbb(Abb<T>& A, T e)
{
    if(!A.buscar(e).vacio())
    {     
        Abb<T> Aux = A.buscar(e);
        while(!Aux.vacio())
        {
            A.eliminar(Aux.elemento());
            Aux.eliminar(Aux.elemento());
        }
    }
}