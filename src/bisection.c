#include "../include/lib.h"

double bissecao(double *cfs, int n, double a, double b){
  // Calcula o valor de f(x) utilizando o método de Bisseção
  double m, funcA = 0;
  int i = 0, k;
  for (k = n; k >= 0; k --){ // Calcula o valor de f(a)
    funcA += cfs[k] * pow(a, k);
  }
  while (b - a >= epsilon || i < 1000){ // Condição de parada
    double funcM = 0;
    m = (a + b) / 2;
    for (k = n; k >= 0; k --){ // Calcula o valor de f(m)
      funcM += cfs[k] * pow(m, k);
    }
    if (funcA * funcM <= 0) // Verifica se f(m) tem o sinal oposto ao de f(a)
      b = m; // Atualiza o valor de b
    else
      a = m; // Atualiza o valor de a
    i++;
  }
  return m;
} // Fim bissecao