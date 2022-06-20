#include "agen.h"

template <typename T>
int ProfundidadAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == A.raiz())
        return 0;
    else return 1 + ProfundidadAgen(A.padre(n), A);
}