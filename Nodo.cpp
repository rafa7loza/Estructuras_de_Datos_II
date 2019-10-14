#include <bits/stdc++.h>
#include "Nodo.h"

using namespace std;

Nodo::Nodo(TipoDato d){
	dato = d;
	sig = nullptr;
}

TipoDato *Nodo::getDato(){
	return &dato;
}

Nodo *Nodo::getSig(){
	return sig;
}
