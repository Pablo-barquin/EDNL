#include "TiposArboles/Abin.h"

template <typename T>
void EliminarElementoAbin(T x, Abin<T>& A)
{
    EliminarElementosAbin_Rec(x, A.raiz(), A);
}

template <typename T>
void EliminarElementosAbin_Rec(T x, typename Abin<T>::nodo n, Abin<T>& A)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.elemento(n) == x)
            ReestructurarAbin(n, A);
        else
        {
            EliminarElementosAbin_Rec(x, A.hijoIzqdo(n), A);
            EliminarElementosAbin_Rec(x, A.hijoDrcho(n), A);
        }
    }
}

template <typename T>
void ReestructurarAbin(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)    // Es nodo hoja
    {
        if(A.hijoIzqdo(A.padre(n)) == n) A.eliminarHijoIzqdo(A.padre(n));   // Lo eliminamos si es hijo Izqdo de su padre
        else A.eliminarHijoDrcho(A.padre(n));   // Lo eliminamos si es hijo Drcho de su padre
    } 
    else if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)   // Tiene hijo Izqdo
    {
        A.elemento(n) = A.elemento(A.hijoIzqdo(n));
        ReestructurarAbin(A.hijoIzqdo(n), A);
    }
    else if(A.hijoDrcho(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)   // Tiene hijo Drcho
    {
        A.elemento(n) = A.elemento(A.hijoDrcho(n));
        ReestructurarAbin(A.hijoDrcho(n), A);
    }
    else    // Tiene los dos hijos
    {
        if(A.elemento(A.hijoIzqdo(n)) > A.elemento(A.hijoDrcho(n))) // Selecciono el menor para mantener el orden 
        {
            A.elemento(n) = A.elemento(A.hijoDrcho(n));
            ReestructurarAbin(A.hijoDrcho(n), A);
        }
        else 
        {
            A.elemento(n) = A.elemento(A.hijoIzqdo(n));
            ReestructurarAbin(A.hijoIzqdo(n), A);
        }
    }
}