#include "../include/lib.h"

int bolzano(double *cfs, int n, double a, double b){
  // Calcula o valor de f(x) utilizando o método de Bolzano
  int x, k, resultado = 0;
  double valorAux = 0;
  for (x = (int)a; x <= b; x ++){ // Calcula o valor de f(x) para cada x
    double valor = 0;
    for (k = n; k >= 0; k --){
      valor += cfs[k] * pow(x, k);
    }
    if (valor * valorAux < 0 || valor == 0){ // Verifica se o valor seja positivo ou igual a zero
      resultado ++; // Raiz encaixa no intervalo
    }
    valorAux = valor;
  }
  return resultado % 2;
} // Fim bolzano