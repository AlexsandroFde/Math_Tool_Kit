#include "../include/lib.h"

void resolverEquacao(){
  // Resolve uma equação de grau n, realizando várias operações matemáticas, como cálculo do intervalo de raízes reais positivas e negativas, aproximação de raízes usando o método da Bisseção e verificação do número de raízes no intervalo usando o método de Bolzano
  int grau, validez, i;
  double *coefs, *coefsAux, inicio, fim; 
  printf("Informe o grau da equação: ");
  validez = scanf("%d", &grau);
  if (validez && grau >= 1){ // Verifica se o grau é válido
    limparBuffer();
    coefs = (double*)malloc(sizeof(double) * (grau + 1));
    coefsAux = (double*)malloc(sizeof(double) * (grau + 1));  
    if (coefs == NULL || coefsAux == NULL){ // Falta de memória
      printf("Erro na alocação de memória\n");
      if (coefs != NULL) free(coefs);
      if (coefsAux != NULL) free(coefsAux);
      return;
    }   
    for (i = grau; i >= 0; i--){ // Lê os coeficientes
      printf("Informe a%d: ", i);
      if (scanf("%lf", &coefs[i]) == 0){
        printf("Entrada inválida. Certifique-se de insirir um valor válido\n");
        limparBuffer();
        free(coefs);
        free(coefsAux);
        return;
      }
    }
    if (coefs[grau] <= 0 || coefs[0] == 0) { // Verifica se a equação é válida
      printf("Os coeficientes não satisfazem os requisitos da equação\n");
      limparBuffer();
      free(coefs);
      free(coefsAux);
      return;
    }
    printf("Intervalo das raizes reais positivas:\n");
    printf("%10.3lf", 1 / lagrange(coefs, coefsAux, grau, 1)); // Intervalo inferior positivo
    printf("%10.3lf\n", lagrange(coefs, coefsAux, grau, 0)); // Intervalo superior positivo
    printf("Intervalo das raizes reais negativas:\n");
    printf("%10.3lf", -lagrange(coefs, coefsAux, grau, 2)); // Intervalo inferior negativo
    printf("%10.3lf\n", -1 / lagrange(coefs, coefsAux, grau, 3)); // Intervalo superior negativo
    printf("Informe um intervalo [a, b] para calcular uma raiz: ");
    validez = scanf("%lf %lf", &inicio, &fim);
    if (validez && inicio < fim){ // Verifica se o intervalo é válido
      if (bolzano(coefs, grau, inicio, fim)){
        printf("Aproximação para umas das raizes: %.3lf\n", bissecao(coefs, grau, inicio, fim));
      }else{
        printf("O número de raízes no intervalo é par");
      }
    }else{
      printf("Entrada inválida. Certifique-se de digitar um intervalo válido\n");
    }
    free(coefs);
    free(coefsAux);
  }else{
    printf("Entrada inválida. Certifique-se de digitar um número inteiro válido\n");
  }
  limparBuffer();
} // Fim resolverEquacao