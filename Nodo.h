#ifndef NODO_H
#define NODO_H

#include <bits/stdc++.h>
#include "TipoDato.h"

using namespace std;

class Nodo{
private:
	TipoDato dato;
	Nodo* sig;
public:
	Nodo(TipoDato d);
	Nodo* getSig();
	void setSig(Nodo* siguiente);
	TipoDato* getDato();
};

#endif // NODO_H

