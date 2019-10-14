#include "ClassA.h"

ClassA::ClassA(int entero, string cadena, int* A)
{
    for (int i = 0; i < 5; i++)
        this->A[i] = A[i];
    this->entero = entero;
    this->cadena = cadena;
}

string ClassA::toString()
{
    stringstream ss;
    ss<<entero<<", "<<cadena<<", ["<<A[0]<<", "<<A[1]<<", "<<A[2]<<", "<<A[3]<<", "<<A[4]<<" ]";

    return ss.str();

}

string ClassA::getCadena() const
{
    return cadena;
}

void ClassA::setCadena(const string &value)
{
    cadena = value;
}

int ClassA::getEntero() const
{
    return entero;
}

void ClassA::setEntero(int value)
{
    entero = value;
}

void ClassA::getA(int* A){
    for (int i = 0; i < 5; i++)
        A[i] = this->A[i];
}
void ClassA::setA(int* A){
    for (int i = 0; i < 5; i++)
        this->A[i] = A[i];
}
