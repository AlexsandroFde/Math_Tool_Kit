#ifndef LIB_H
#define LIB_H
#include <stdio.h>
#include <stdlib.h>

void limparBuffer();
void systemClear();
void inverter(char *str);

char *converter(char *res, double num, int base);

#endif