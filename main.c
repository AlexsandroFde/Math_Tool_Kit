#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#define epsilon 0.00000001

void systemClear(){
  // Limpa o console, utilizando comandos do sistema operacional dependendo da plataforma (Linux ou Windows)
  #ifdef __linux__
  system("clear");
  #elif _WIN32
  system("cls");
  #else
  #endif
} // Fim systemClear

void limparBuffer(){
  // Limpa o buffer do teclado, removendo qualquer entrada pendente
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {}
} // Fim limparBuffer

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

char *converter(char *res, double num, int base){
  // Converte um número decimal para uma base específica, como binário, octal ou hexadecimal, e armazena o resultado em uma string
  int parteInt = (int)num, i = 0, tamanhoMax = 20;
  double parteFrc = num - parteInt;
  while (parteInt > 0){ // Faz sucessivas divisões pela base até que o resultado seja 0
    int resto = parteInt % base;
    res[i++] = (resto < 10) ? (char)(resto + '0') : (char)(resto - 10 + 'A');
    parteInt /= base;
  }
  if (i == 0){
    res[i++] = '0';
  }
  res[i] = '\0';
  inverter(res); // Inverte a string para armazenar o resultado correto
  if (parteFrc > 0){
    res[i++] = '.';
    while (parteFrc > 0 && tamanhoMax > 0){ // Faz sucessivas multiplicações pela base até que o resultado seja 0 ou atinja o limite de casas decimais
      parteFrc *= base;
      int digito = (int)parteFrc;
      res[i++] = (digito < 10) ? (char)(digito + '0') : (char)(digito - 10 + 'A');
      parteFrc -= digito;
      tamanhoMax--;
    }
    res[i] = '\0';
  }
  return res;
} // Fim converter

void converterBOH(){
  // Converte um número decimal para binário, octal e hexadecimal
  double number;
  int validez;
  printf("Digite um número decimal: ");
  validez = scanf("%lf", &number);
  if (validez && number >= 0){ // Validação do número decimal
    char resultado[100]; // Armazena o resultado da conversão
    printf("Binário: %s\n", converter(resultado, number, 2)); // Binário
    printf("Octal: %s\n", converter(resultado, number, 8)); // Octal
    printf("Hexadecimal: %s\n", converter(resultado, number, 16)); // Hexadecimal
  }else{
    printf("Entrada inválida. Certifique-se de digitar um número decimal válido\n");
  }
  limparBuffer();
}// Fim converterBOH

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
    printf("Erro na alocação de memória\n");
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
      printf("Erro na alocação de memória\n");
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
      printf("O sistema é compativel\n");
      printf("Solução do sistema:\n");
      for (i = 0; i < n; i++){
        printf("x%d = %.3lf\n", i + 1, xi[i]); // Imprime a solução
      }
    } else{
      printf("O sistema é incompatível\n");
    }
  }else{ // Falta de memória
    printf("Erro na alocação de memória\n");
    if (xi != NULL) free(xi);
    if (xAux != NULL) free(xAux);
  }
  for (i = 0; i < n; i++){
    free(matriz[i]);
  }
  free(matriz);
} // Fim sistemaLinear

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

double bissecao(double *cfs, int n, double a, double b){
  // Calcula o valor de f(x) utilizando o método de Bisseção
  double m, funcA = 0, funcB = 0;
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

int main(void){
  char opc;
  do{
    printf("\n<-=~={ MENU }=~=->\n");
    printf("'C' - Conversão\n");
    printf("'S' - Sistema Linear\n");
    printf("'E' - Equação Algébrica\n");
    printf("'F' - Finalizar\n");
    printf("Escolha uma opção: ");
    opc = fgetc(stdin);
    limparBuffer();
    printf("\n");
    systemClear();
    switch (opc){
      case 'C':
        converterBOH();
        break;
      case 'S':
        sistemaLinear();
        break;
      case 'E':
        resolverEquacao();
        break;
      case 'F':
        printf("Programa finalizado\n");
        break;
      default:
        printf("Opção inválida. Tente novamente\n");
    }
  }while (opc != 'F');
  return 0;
}