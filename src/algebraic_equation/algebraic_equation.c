#include "../include/lib.h"

void resolverEquacao(){
  // Resolve uma equação de grau n, realizando várias operações matemáticas, como cálculo do intervalo de raízes reais positivas e negativas, aproximação de raízes usando o método da Bisseção e verificação do número de raízes no intervalo usando o método de Bolzano
  int grau, validez, i;
  double *coefs, *coefsAux, inicio, fim; 
  printf("Informe o grau da equacao: ");
  validez = scanf("%d", &grau);
  if (validez && grau >= 1){ // Verifica se o grau é válido
    limparBuffer();
    coefs = (double*)malloc(sizeof(double) * (grau + 1));
    coefsAux = (double*)malloc(sizeof(double) * (grau + 1));  
    if (coefs == NULL || coefsAux == NULL){ // Falta de memória
      printf("Erro na alocacao de memoria\n");
      if (coefs != NULL) free(coefs);
      if (coefsAux != NULL) free(coefsAux);
      return;
    }   
    for (i = grau; i >= 0; i--){ // Lê os coeficientes
      printf("Informe a%d: ", i);
      if (scanf("%lf", &coefs[i]) == 0){
        printf("Entrada invalida. Certifique-se de insirir um valor valido\n");
        limparBuffer();
        free(coefs);
        free(coefsAux);
        return;
      }
    }
    if (coefs[grau] <= 0 || coefs[0] == 0) { // Verifica se a equação é válida
      printf("Os coeficientes nao satisfazem os requisitos da equacao\n");
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
        printf("Aproximacao para umas das raizes: %.3lf\n", bissecao(coefs, grau, inicio, fim));
      }else{
        printf("O numero de raizes no intervalo eh par");
      }
    }else{
      printf("Entrada invalida. Certifique-se de digitar um intervalo valido\n");
    }
    free(coefs);
    free(coefsAux);
  }else{
    printf("Entrada invalida. Certifique-se de digitar um numero inteiro valido\n");
  }
  limparBuffer();
} // Fim resolverEquacao