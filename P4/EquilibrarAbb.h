#include "Abb.h"
#include "vector"

template <typename T>
void EquilibrarAbb(Abb<T>& A)
{
    Abb<T> B;
    std::vector<T> Vector;
    InordenAbb(A, Vector);

    EquilibrarAbb_Rec(B, Vector, 0, Vector.size()-1);
    A = B;
}

template <typename T>
void EquilibrarAbb_Rec(Abb<T>& A, std::vector<T> Vec, int inicio, int final)
{
    int mediana;
    if(inicio <= final)
    {
        mediana = ((final - inicio) / 2) + inicio;
        A.insertar(Vec.at(mediana));
        EquilibrarAbb_Rec(A, Vec, inicio, mediana-1);
        EquilibrarAbb_Rec(A, Vec, mediana+1, final);
    }
}

template <typename T>
void InordenAbb(const Abb<T>& A, std::vector<T>& Recorrido)
{
    if(!A.vacio())
    {
        InordenAbb(A.izqdo(), Recorrido);
        Recorrido.push_back(A.elemento());
        InordenAbb(A.drcho(), Recorrido);
    }

}
