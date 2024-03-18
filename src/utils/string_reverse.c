#include "../include/lib.h"

void inverter(char *str){
  // Inverte uma string passada como argumento
  int tam = strlen(str);
  int comeco = 0;
  int fim = tam - 1;
  while (comeco < fim){
    char aux = str[comeco];
    str[comeco] = str[fim];
    str[fim] = aux;
    comeco++;
    fim--;
  }
} // Fim inverter