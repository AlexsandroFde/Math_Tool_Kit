#include "../include/lib.h"

int main(void){
  char opc;
  do{
    printf("\n<-=~={ MENU }=~=->\n");
    printf("'C' - Conversao\n");
    printf("'S' - Sistema Linear\n");
    printf("'E' - Equacao Algebrica\n");
    printf("'F' - Finalizar\n");
    printf("Escolha uma opcao: ");
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
        printf("Opcao invalida. Tente novamente\n");
    }
  }while (opc != 'F');
  return 0;
}