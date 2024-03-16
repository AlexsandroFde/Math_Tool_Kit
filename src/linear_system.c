#include "../include/lib.h"

void sistemaLinear(){
  // Resolve o sistema linear de equações utilizando o método de Jordan
  int n, i, j, *xAux, compativel;
  double **matriz, *xi;
  char nomeArq[100];
  FILE *arq;
  printf("Digite o nome do arquivo: ");
  fgets(nomeArq, sizeof(nomeArq), stdin); // Lê o nome do arquivo
  nomeArq[strlen(nomeArq) - 1] = '\0'; // Remove o caractere de nova linha
  arq = fopen(nomeArq, "r");
  if (arq == NULL){ // Caso o arquivo não exista
    printf("Erro ao abrir o arquivo\n");
    return;
  }
  fscanf(arq, "%d", &n);
  matriz = (double**)malloc(sizeof(double*) * n);
  if (matriz == NULL){ // Falta de memória
    printf("Erro na alocacao de memoria\n");
    fclose(arq);
    return;
  }
  for (i = 0; i < n; i++){ // Aloca as linhas da matriz
    matriz[i] = (double*)malloc(sizeof(double) * (n + 1));
    if (matriz[i] == NULL){ // Falta de memória
      for (j = 0; j < i; j++){
        free(matriz[j]);
      }
      free(matriz);
      printf("Erro na alocacao de memoria\n");
      fclose(arq);
      return;
    }
    for (j = 0; j <= n; j++){ // Lê os valores da matriz
      fscanf(arq, "%lf", &matriz[i][j]);
    }
  }
  fclose(arq); // Fecha o arquivo
  xi = (double*)malloc(sizeof(double) * n);
  xAux = (int*)malloc(sizeof(int) * n);
  if (xi != NULL && xAux != NULL){
    for (i = 0 ; i < n; i++) {
      xi[i] = i;
      xAux[i] = i;
    }
    compativel = jordan(matriz, n, xi, xAux); // Resolve o sistema linear
    printf("Matriz diagonal:\n");
      for (i = 0; i < n; i++){
        for (j = 0; j <= n; j++){
          printf("%10.3lf ", matriz[i][j]);
        }
        printf("\n");
      }
    if (compativel){ // Caso o sistema linear seja compativel
      printf("O sistema eh compativel\n");
      printf("Solucao do sistema:\n");
      for (i = 0; i < n; i++){
        printf("x%d = %.3lf\n", i + 1, xi[i]); // Imprime a solução
      }
    } else{
      printf("O sistema eh incompativel\n");
    }
  }else{ // Falta de memória
    printf("Erro na alocacao de memoria\n");
    if (xi != NULL) free(xi);
    if (xAux != NULL) free(xAux);
  }
  for (i = 0; i < n; i++){
    free(matriz[i]);
  }
  free(matriz);
} // Fim sistemaLinear