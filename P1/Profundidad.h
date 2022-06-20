#include "Abin.h"

template <typename T>
int Profundidad(Abin<T>& A, typename Abin<T>::nodo n)
{
    if(n == A.raiz())
        return 0;
    else return 1 + Profundidad(A, A.padre(n));
}