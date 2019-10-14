#ifndef LISTA_H
#define LISTA_H

#include <bits/stdc++.h>
#include "TipoDato.h"
#include "Nodo.h"

using namespace std;

class Lista{
private:
	int cont;
	Nodo* primero;
public:
	Lista();
	TipoDato* getDato();
	void insertaFinal(TipoDato buscado);
	//Nodo* busca(TipoDato buscado);
	//void elimina(Nodo* e);
};


#endif // LISTA_H
