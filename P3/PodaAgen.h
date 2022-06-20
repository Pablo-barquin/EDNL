#include "agen.h"


void EliminarNodos(typename Agen<int>::nodo n, Agen<int>& A)
{
    typename Agen<int>::nodo hijo = A.hijoIzqdo(n);
    while(hijo != Agen<int>::NODO_NULO)
    {
        EliminarNodos(hijo, A);
        if(hijo != Agen<int>::NODO_NULO)
            A.eliminarHijoIzqdo(n);
        hijo = A.hijoIzqdo(n);
    }

}

int PodaAgen_Rec(typename Agen<int>::nodo n, Agen<int>& A, int num)
{
    bool Flag = false;
    if(n == Agen<int>::NODO_NULO)
        return Flag;
    else
    {   
        if(A.elemento(n) == num)
        {
            EliminarNodos(n, A);
            A.eliminarHijoIzqdo(A.padre(n));
            return true;
        }
        else
        {
            n = A.hijoIzqdo(n);    
            while(n != Agen<int>::NODO_NULO && Flag == false)
            {
                Flag = PodaAgen_Rec(n, A, num);
                n = A.hermDrcho(n);
            }
            return Flag;
        }
    }
}

void PodaAgen(Agen<int>& A, int n)
{
    PodaAgen_Rec(A.raiz(), A, n);
}