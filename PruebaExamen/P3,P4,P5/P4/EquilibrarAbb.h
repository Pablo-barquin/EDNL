#include "Abb.h"
#include "vector"

template <typename T>
void EquilibrarAbb(Abb<T>& A)
{
    if(!A.vacio())
    {
        Abb<T> B;

        vector<T> ElementosAbb;
        InsertarElementos(ElementosAbb, A);

        EquilibrarAbb_Rec(ElementosAbb, B, 0, ElementosAbb.size()-1);
        A = B;
    }
}

template <typename T>
void EquilibrarAbb_Rec(vector<T> v1, Abb<T>& B, int inicio, int fin)
{
    if(inicio <= fin)
    {
        int mediana = (inicio+fin)/2;
        B.insertar(v1.at(mediana));
        EquilibrarAbb_Rec(v1, B, inicio, mediana-1);
        EquilibrarAbb_Rec(v1, B, mediana+1, fin);
    }
}

template <typename T>
void InsertarElementos(vector<T>& v1, const Abb<T>& A)
{
    if(!A.vacio())
    {
        InsertarElementos(v1, A.izqdo());
        v1.push_back(A.elemento());
        InsertarElementos(v1, A.drcho());
    }
}