/*******************

Nombre:       Loza Arechiga Andre Rafael
Codigo:       214589252
Asignatura:   Seminario de Solucion de Problemas
              De Estructuras de Datos 2
Seccion:      D18
Profesor:     Guerrero Segura Ramirez Miguel Angel

********************/

#include <stdio.h>

const int RANGE = 10;

int main(){
  int digits[RANGE] = {0};
  int white=0, others=0, i;
  char c;

  while((c = getchar()) != EOF){
    if(c >= '0' && c <= '9') ++digits[c-'0'];
    else if(c == '\n' || c == '\t' || c == ' ') ++white;
    else ++others;
  }

  for(i=0; i<RANGE; ++i)
    printf("El digito %d aparece %d veces.\n", i, digits[i]);
  printf("Hay %d espacios blancos.\n", white);
  printf("Hay %d otros caracteres.\n", others);

}
