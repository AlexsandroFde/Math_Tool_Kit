#ifndef LIB_H
#define LIB_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#define epsilon 0.00000001

void limparBuffer();
void systemClear();
void inverter(char *str);

char *converter(char *res, double num, int base);
void converterBOH();

int jordan(double **matriz, int n, double *x, int *aux);
void sistemaLinear();

double lagrange(double *a, double *aAux, int n, int tipo);
int bolzano(double *cfs, int n, double a, double b);
double bissecao(double *cfs, int n, double a, double b);
void resolverEquacao();

#endif