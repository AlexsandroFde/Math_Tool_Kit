#include "../include/lib.h"

void systemClear(){
  // Limpa o console, utilizando comandos do sistema operacional dependendo da plataforma (Linux ou Windows)
  #ifdef __linux__
  system("clear");
  #elif _WIN32
  system("cls");
  #else
  #endif
} // Fim systemClear