#include "../include/lib.h"

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