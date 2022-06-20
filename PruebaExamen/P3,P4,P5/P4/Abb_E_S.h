#ifndef ABB_E_S_H
#define ABB_E_S_H

#include <iostream>
#include <fstream>
#include "Abb.h"

using namespace std;

template <typename T>
void mostrarAbb(const Abb<T>& A){
    
    if(!A.vacio()){
        cout << "Raiz del Arbol: " << A.elemento() << endl;
        if(!A.izqdo().vacio())
        {
            cout << "Hijo Izqdo de " << A.elemento() << ": ";
            mostrar(A.izqdo());
        }
        if(!A.drcho().vacio())
        {
            cout << "Hijo Drcho de " << A.elemento() << ": ";
            mostrar(A.drcho());
        }
    }
}

template <typename T>
void mostrar(const Abb<T>& A){
    
    cout << A.elemento() << endl;
    if(!A.izqdo().vacio())
    {
        cout << "Hijo Izqdo de " << A.elemento() << ": ";
        mostrar(A.izqdo());
    }
    if(!A.drcho().vacio())
    {
        cout << "Hijo Drcho de " << A.elemento() << ": ";
        mostrar(A.drcho());
    }
}

//Insertar elementos al Abb desde fichero
template <typename T>
void insertarAbb(istream& f, Abb<T>& A){
    T ins;
    while (f >> ins){
        A.insertar(ins);
    }
}

//Insertar elementos al Abb desde teclado
template <typename T>
void insertarAbb(Abb<T>& A, const T fin)
{
    T entrada;
    cout << "Introduzca elemento (Fin = " << fin << "): ";
    cin >> entrada;
    while(entrada != fin)
    {
        A.insertar(entrada);
        cout << "Introduzca elemento (Fin = " << fin << "): ";
        cin >> entrada;
    }
}

#endif //ABB_E_S_H