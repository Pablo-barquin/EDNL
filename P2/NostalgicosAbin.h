#include "Abin.h"

template <typename T>
int NostalgicosAbin(Abin<T>& A)
{
    return NostalgicosAbin_Rec(A.raiz(), A);
}

template <typename T>
int NostalgicosAbin_Rec(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else if(A.Profundidad(n) > NumNodos_Rec(n, A)-1)
            return 1 + NostalgicosAbin_Rec(A.hijoIzqdo(n), A) + NostalgicosAbin_Rec(A.hijoDrcho(n), A);
    else return NostalgicosAbin_Rec(A.hijoIzqdo(n), A) + NostalgicosAbin_Rec(A.hijoDrcho(n), A);
}

template <typename T>
int NumNodos_Rec(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else return 1 + NumNodos_Rec(A.hijoIzqdo(n), A) + NumNodos_Rec(A.hijoDrcho(n), A);
}