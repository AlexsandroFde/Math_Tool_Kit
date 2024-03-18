#include "../include/lib.h"

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