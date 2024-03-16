#include "../include/lib.h"

double lagrange(double *a, double *aAux, int n, int tipo) {
  // Calcula o intervalo das raizes de f(x) utilizando o método de Lagrange
  int k = 0, inverter = (tipo == 1 || tipo == 3), negImpar = (tipo == 2 || tipo ==3), i;
  double B = 0, an;
  for (i = 0; i <= n; i++){ // Cria um vetor de coeficiente auxiliar
    aAux[inverter ? n - i : i] = a[i]; // Faz a inversão do vetor se o tipo for 1 ou 3
  }
  if (negImpar){ // Faz a negação dos coeficientes impares se o tipo for 2 ou 3
    for (i = 1; i <= n; i += 2){
        aAux[i] = - aAux[i];
    }
  }
  if (aAux[n] < 0){ // Inverte o sinal dos coefientes se aAux[n] for negativo
    for (i = 0; i <= n; i++){
      aAux[i] = -aAux[i];
    }
  }
  an = aAux[n]; // Salva o coeficiente aAux[n] em an
  for (i = n; i > 0; i --){
    if (aAux[i] < 0) {
      if (i > k){ // Salva o maior indice dente os coefientes negativos
        k = i;
      }
      double aux = fabs(aAux[i]); 
      if (aux > B){ // Salva o maior coeficiente absoluto em B
        B = aux;
      }
    }
  }
  return 1 + pow(B / an, 1.0 / (n - k)); // Retorna L, L1, L2 ou L3
} // Fim lagrange