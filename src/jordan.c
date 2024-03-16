#include "../include/lib.h"

int jordan(double **matriz, int n, double *x, int *aux){
  // Resolve o sistema de equações lineares utilizando o método de Jordan
  int i, j, k, xLivre;
  for (i = 0; i < n; i++){ 
    if (matriz[i][i] == 0){ // Se matriz[i][i] for igual a 0, encontramos uma coluna j com o coeficiente diferente de 0
      for (j = i + 1; j < n; j++){
        aux[i] = j;
        aux[j] = i;
        if (matriz[j][i] != 0){ // Se matriz[j][i] for diferente de 0, então encontramos uma
          for (k = 0; k < n; k++){ // Trocamos a coluna i pela coluna j
            double aux = matriz[k][i];
            matriz[k][i] = matriz[k][j];
            matriz[k][j] = aux;
          }       
        }else if(j == n - 1){ // Se j for igual a n - 1, então o sistema não possui tal coluna
          for (k = 0; k < n; k++){ // Zera a coluna i
            matriz[k][i] = 0;
          }
        }
      }
    }
    if (matriz[i][i] != 0){
      for (j = 0; j < n; j++){
        if (j != i){ // Subtraímos a linha i da linha j
          double m = matriz[j][i] / matriz[i][i];
          matriz[j][i] = 0;
          for (k = i + 1; k <= n; k++){
            matriz[j][k] -= m * matriz[i][k];
          }
        }
      }
    }
  }
  for (i = 0 ; i < n; i++){ // Resolvemos o sistema utilizando a eliminação de Gauss
    xLivre = fabs(matriz[i][i]) < epsilon; // Variável livre
    x[aux[i]] = xLivre ? 0.0 : matriz[i][n] / matriz[i][i];
    if (xLivre && fabs(matriz[i][n]) > epsilon){
      return 0;
    }
  }
  return 1;
} // Fim jordan