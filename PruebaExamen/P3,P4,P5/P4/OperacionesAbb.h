#include "Abb.h"
#include "EquilibrarAbb.h"

typedef Abb<int> Conjunto;

Conjunto Union(Conjunto A, Conjunto B)
{
    while(!B.vacio())
    {
        A.insertar(B.elemento());
        B.eliminar(B.elemento());
    }

    EquilibrarAbb(A);

    return A;
}

Conjunto Interseccion(Conjunto A, Conjunto B)
{
    Conjunto C;
    
    while(!B.vacio())
    {
        if(!A.buscar(B.elemento()).vacio())
            C.insertar(B.elemento());
        B.eliminar(B.elemento());
    }

    EquilibrarAbb(C);

    return C;
}

Conjunto Rombo(Conjunto A, Conjunto B)
{
    Conjunto C, D, Final;

    C = Union(A, B);
    D = Interseccion(A, B);

    while(!C.vacio())
    {
        if(D.buscar(C.elemento()).vacio())
            Final.insertar(C.elemento());
        C.eliminar(C.elemento());
    }

    EquilibrarAbb(Final);

    return Final;
}
