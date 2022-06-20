#include "Abin.h"

template <typename T>
void TransformacionAbin(Abin<T>& A)
{
    return TransformacionAbin_Rec(A.raiz(), A);
}

template <typename T>
void TransformacionAbin_Rec(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(MayorAscendientes(A.padre(n), n, A) && MenorDescendientes(n, A))
            EliminarNodos(n, A);
        else
        {
            TransformacionAbin_Rec(A.hijoIzqdo(n), A);
            TransformacionAbin_Rec(A.hijoDrcho(n), A);
        }
    }
}

template <typename T>
bool MayorAscendientes(typename Abin<T>::nodo Asc, typename Abin<T>::nodo n, Abin<T>& A)
{
    if(Asc == Abin<T>::NODO_NULO)
        return true;
    else if(A.elemento(n).Booleano >= A.elemento(Asc))
        return MayorAscendientes(A.padre(Asc), n, A);
    else false;
}

template <typename T>
bool MenorDescendientes(typename Abin<T>::nodo n, Abin<T>& A)
{
    return MenorDescendientes_Rec(A.hijoIzqdo(n), n, A) && MenorDescendientes_Rec(A.hijoDrcho(n), n, A);
}

template <typename T>
bool MenorDescendientes_Rec(typename Abin<T>::nodo Des, typename Abin<T>::nodo n, Abin<T>& A)
{
    if(Des == Abin<T>::NODO_NULO)
        return true;
    else if(A.elemento(n) <= A.elemento(Des))
        return MenorDescendientes_Rec(A.hijoIzqdo(Des), n, A) && MenorDescendientes_Rec(A.hijoDrcho(Des), n, A);
    else return false;
}

template <typename T>
void EliminarNodos(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(n != Abin<T>::NODO_NULO)
    {
        EliminarNodos(A.hijoIzqdo(n), A);
        EliminarNodos(A.hijoDrcho(n), A);
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
            A.eliminarHijoIzqdo(n);
        if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)
            A.eliminarHijoDrcho(n);
    }
}