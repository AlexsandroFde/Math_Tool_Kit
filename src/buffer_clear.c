#include "../include/lib.h"

void limparBuffer(){
  // Limpa o buffer do teclado, removendo qualquer entrada pendente
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {}
} // Fim limparBuffer