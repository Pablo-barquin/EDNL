#ifndef ABINALTURA_H
#define ABINALTURA_H
#include <cassert>
#include <math.h>
#include <iostream>

using std::pow;

template <typename T> class AbinAltura {
public:
    typedef size_t nodo;
    static const nodo NODO_NULO;

    AbinAltura(int H, const T& e_nulo);

    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    nodo raiz();
    nodo padre(nodo n); 
    nodo HijoIzqdo(nodo n); 
    nodo HijoDrcho(nodo n);

private:
    T *nodos;
    T ELTO_NULO;
    size_t MaxNodos;
    size_t Altura;

    int ProfundidadNodo(nodo n);
};

/*--------------------------------------------------------*/
/* Métodos públicos */
/*--------------------------------------------------------*/
template <typename T>
const typename AbinAltura<T>::nodo AbinAltura<T>::NODO_NULO(-1);

template <typename T>
int AbinAltura<T>::ProfundidadNodo(nodo n)
{
    int inicio = 0, pos = MaxNodos/2, fin = MaxNodos-1;
    int profundidad = 0;

    while(n != pos && inicio <= fin)
    {
        if(pos < n)
            inicio = pos+1;
        else
            fin = pos-1;
        
        pos = (inicio+fin)/2;
        profundidad++;
    }
    
    return profundidad;

    // if(inicio >= fin || n != pos)
    // {
    //     std::cout << "No se ha encontrado el elemento" << std::endl;
    //     exit(-1);
    // }
    
}

// template <typename T>
// int AbinAltura<T>::AlturaNodo(nodo n)
// {
//     int profundidad = 0;
//     int r = raiz();
//     while(n != r)
//     {
//         n = padre(n);
//         profundidad++;
//     }
    
//     return (Altura - profundidad);
// }

template <typename T>
AbinAltura<T>::AbinAltura(int H, const T& e_nulo):
    nodos(new T[(int)pow(2, H+1)-1]),
    MaxNodos(pow(2, H+1)-1),
    Altura(H),
    ELTO_NULO(e_nulo)
{
    for(nodo n = 0; n <= MaxNodos-1; n++)
        nodos[n] = ELTO_NULO;
}

template <typename T>
void AbinAltura<T>::insertarRaiz(const T& e)
{
    int pos = MaxNodos/2;
    assert(nodos[pos] == ELTO_NULO);

    nodos[pos] = e;
    std::cout << "Inserto raiz " << e << " en posicion " << pos << std::endl;
}

template <typename T>
void AbinAltura<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n > 0 && n < MaxNodos);      //Que este dentro del rango de nodos
    assert(nodos[n] != ELTO_NULO);      //Existe el nodo
    
    int h = Altura - ProfundidadNodo(n);
    int pos = n-pow(2, h-1);  //Calculo la nueva posicion del hizq
    
    assert(pos < MaxNodos); // Hijo Izqdo. cabe en el arbol
    assert(nodos[pos] == ELTO_NULO); // n no tiene Hizq
    
    nodos[pos] = e;
    std::cout << "Inserto elemento " << e << " como hizq de " << n << " en posicion " << pos << std::endl;
}

template <typename T>
void AbinAltura<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n > 0 && n < MaxNodos);      //Que este dentro del rango de nodos
    assert(nodos[n] != ELTO_NULO);      //Existe el nodo
    
    int h = Altura - ProfundidadNodo(n);
    int pos = n+pow(2, h-1);  //Calculo la nueva posicion del hizq
    
    assert(pos < MaxNodos); // Hijo Izqdo. cabe en el arbol
    assert(nodos[pos] == ELTO_NULO); // n no tiene Hizq
    nodos[pos] = e;
    std::cout << "Inserto elemento " << e << " como hder de " << n << " en posicion " << pos << std::endl;
}

template <typename T>
typename AbinAltura<T>::nodo AbinAltura<T>::raiz()
{
    return (nodos[MaxNodos/2] != ELTO_NULO) ? MaxNodos/2 : NODO_NULO;
}

template <typename T>
typename AbinAltura<T>::nodo AbinAltura<T>::padre(nodo n)
{
    assert(n > 0 && n < MaxNodos);
    assert(nodos[n] != ELTO_NULO);
    
    int h = Altura - ProfundidadNodo(n);
    if(n%(int)pow(2, h+2) == pow(2, h)-1)
        return (n == MaxNodos/2) ? NODO_NULO : (int)n+pow(2, h);
    else
        return (n == MaxNodos/2) ? NODO_NULO : (int)n-pow(2, h);
}

template <typename T>
typename AbinAltura<T>::nodo AbinAltura<T>::HijoIzqdo(nodo n)
{
    assert(n > 0 && n < MaxNodos);
    assert(nodos[n] != ELTO_NULO);
    
    int h = Altura - ProfundidadNodo(n);
    return ((n-(int)pow(2, h-1)) >= MaxNodos || nodos[n-(int)pow(2, h-1)] == ELTO_NULO) ?
        NODO_NULO : n-pow(2, h-1);
}

template <typename T>
typename AbinAltura<T>::nodo AbinAltura<T>::HijoDrcho(nodo n) 
{
    assert(n > 0 && n < MaxNodos);
    assert(nodos[n] != ELTO_NULO);
    
    int h = Altura - ProfundidadNodo(n);
    return ((n+(int)pow(2, h-1)) >= MaxNodos || nodos[n+(int)pow(2, h-1)] == ELTO_NULO) ?
        NODO_NULO : (int)n+pow(2, h-1);
}

#endif