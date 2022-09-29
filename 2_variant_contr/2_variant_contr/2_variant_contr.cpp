#include "pch.h"
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#pragma warning(disable: 4996);
using namespace std;

double lagr(int n, double *xt, double *yt, double x) {
	double result1=1,result2=0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n;++j) {
			if (j!=i){
				result1 *= (x - xt[j]);
			}			
		}
		for (int j = 0; j < n; ++j) {
			if (j != i) {
				result1 /= (xt[i] - xt[j]);
			}
		}
		result1 *=yt[i];
		result2 += result1;
		result1 = 1;
	}
	return result2;
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n=0;
	double *xt, *yt;
	double x;
	while (n == 0) {
		printf("\nВведите количество узлов ");
		scanf("%d", &n);
		if (n == 0) {
			printf("\nВы должны ввести целое число больше 0\n ");
		}
	}
	xt = (double*)malloc(sizeof(double)*n);
	yt = (double*)malloc(sizeof(double)*n);
	printf("\nВведите абсциссу, в которой вычисляется значение многочлена ");
	scanf("%lf", &x);
	printf("\nВведите абсциссы и ординаты узловых точек\n");
	for (int i = 0; i < n; ++i) {
		printf("\nxt[%d]=", i);
		scanf("%lf", &xt[i]);
		printf("\nyt[%d]=",i);
		scanf("%lf", &yt[i]);
	}
	double result = lagr(n,xt,yt,x);
	printf("Значение интерполяционного многочлена Лагранжа %lf",result);
	return 0;
}