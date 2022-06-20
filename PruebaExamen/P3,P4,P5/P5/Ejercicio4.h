#include "TiposArboles/agen.h"

template <typename T>
bool esTernarioAgen(const Agen<T>& A)
{
    return esTernarioAgen_Rec(A.raiz(), A);
}

template <typename T>
bool esTernarioAgen_Rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool flag = true;
        int nodos = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            nodos++;
            flag = esTernarioAgen_Rec(hijo, A) && flag;
            hijo = A.hermDrcho(hijo);
        }

        if(nodos == 3 || nodos == 0) return flag && true;
        else return false;
    }
}