#include "Abb.h"
#include "EquilibrarAbb.h"

template <typename T>
Conjunto<T> Union(Conjunto<T> A, Conjunto<T> B)
{
    T e;
    while(!B.vacio())
    {
        e = B.elemento();
        if(A.buscar(e).vacio())
           A.insertar(e);
        B.eliminar(e);
    }  

    EquilibrarAbb(A);
    return A; 
}

template <typename T>
Conjunto<T> Interseccion(Conjunto<T> A, Conjunto<T> B)
{
    Conjunto<T> C;

    T e;
    while(!B.vacio())
    {
        e = B.elemento();
        if(!A.buscar(e).vacio())
            C.insertar(e);
        B.eliminar(e);
    }

    EquilibrarAbb(C);
    return C;
}

template <typename T>
Conjunto<T> Rombo(Conjunto<T> A, Conjunto<T> B)
{
    Conjunto<T> C, D;

    C = Union(A, B);
    D = Interseccion(A, B);

    T e;
    while(!D.vacio())
    {
        e = D.elemento();
        if(!C.buscar(e).vacio())
            C.eliminar(e);
        D.eliminar(e);
    }

    EquilibrarAbb(C);
    return C;
}
