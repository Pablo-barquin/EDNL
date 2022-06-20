#include "Abin.h"

template <typename T>
bool PseudoArbol(Abin<T> A)
{
    if(A.arbolVacio())
        return true;
    else return PseudoArbol_Rec(A, A.raiz(), 0);
}

template <typename T>
bool PseudoArbol_Rec(Abin<T> A, typename Abin<T>::nodo n, int Nivel)
{
    typename Abin<T>::nodo nulo;
    nulo = Abin<T>::NODO_NULO;
    if(n == nulo)
        return true;
    else
    {
        if(Nivel != A.Altura(A.raiz()) - 1)
            return (PseudoArbol_Rec(A, A.hijoIzqdo(n), Nivel+1) && PseudoArbol_Rec(A, A.hijoDrcho(n), Nivel+1));
        else
        {
            if(A.hijoIzqdo(n) == nulo && A.hijoDrcho(n) == nulo)
                return true;
            else if(A.hijoIzqdo(n) == nulo || A.hijoDrcho(n) == nulo)
                return false;
            else return true;            
        }
    }
}

/**
 *  sino Altura >= 1
 *      si Altura(HijoIzqdo(n, A)) > Altura(HijoDrcho(n, A))
 *          Devolver Pseudo_Rec(HijoIzqdo, n, A)
 *      sino
 *          si Altura(HijoDrcho(n, A)) > Altura(HijoIzqdo(n, A))
 *              Devolver Pseudo_Rec(HijoDrcho, n, A)
 *          sino
 *              Devolver Pseudo_Rec(HijoIzqdo, n, A) && Pseudo_Rec(HijoDrcho, n, A)    
 */