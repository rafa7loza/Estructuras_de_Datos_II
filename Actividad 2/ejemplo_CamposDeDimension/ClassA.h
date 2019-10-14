#ifndef CLASSA_H
#define CLASSA_H
#include <string>
#include <sstream>

using namespace std;

class ClassA
{
private:
    int entero;
    string cadena;
    int A[5];
public:

    ClassA(int entero, string cadena, int* A);
    string toString();


    int getEntero() const;
    void setEntero(int value);
    string getCadena() const;
    void setCadena(const string &value);
    void getA(int* A);
    void setA(int* A);
};

#endif // CLASSA_H
