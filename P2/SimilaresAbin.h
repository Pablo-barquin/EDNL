#include "Abin.h"

template <typename T>
bool SimilaresAbin(const Abin<T>& A, const Abin<T>& B)
{
    return SimilaresAbin_Rec(A.raiz(), B.raiz(), A, B);
}

template <typename T>
bool SimilaresAbin_Rec(typename Abin<T>::nodo na, typename Abin<T>::nodo nb, const Abin<T>& A, const Abin<T>& B)
{
    typename Abin<T>::nodo nulo;
    nulo = Abin<T>::NODO_NULO;

    if(na == nulo && nb == nulo)
        return true;
    else if(na == nulo || nb == nulo)
        return false;
    else return (SimilaresAbin_Rec(A.hijoIzqdo(na), B.hijoIzqdo(nb), A, B) && SimilaresAbin_Rec(A.hijoDrcho(na), B.hijoDrcho(nb), A, B));
}