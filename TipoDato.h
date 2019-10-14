#ifndef TIPO_DATO_H
#define TIPO_DATO_H
#include <bits/stdc++.h>

using namespace std;

class TipoDato{
private:
	int entero;
	string cadena;
	float flotante;
public:
	TipoDato();
	TipoDato(int _entero, string _cadena, float _flotante);
	bool operator ==(TipoDato der);// devuelve un true o false a la instrucción
};

#endif // TIPO_DATO_H