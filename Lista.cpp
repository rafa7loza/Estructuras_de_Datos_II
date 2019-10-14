#include <bits/stdc++.h>
#include "Lista.h"
using namespace std;

Lista::Lista(){
	primero = nullptr;
	cont = 0;
}

void Lista::insertaFinal(TipoDato buscado){
	Nodo* temp = new Nodo(buscado);
	if(primero = nullptr){
		primero = temp;
	}else{
		temp->getSig() = primero;
		primero = temp;
	}
}

TipoDato* Lista::getDato(){
	return primero->getDato();
}