#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#pragma warning (disable: 4996)
using namespace std;
int GaussianElimination(const int n, double** a, double* b, double* x)
{
	
	double** ab = (double**)malloc(n * sizeof(double*));

	for (int i = 0; i < n; i++)
	{
		ab[i] = (double*)malloc((n + 1) * sizeof(double));

		for (int j = 0; j < n; j++)
			ab[i][j] = a[i][j];

		ab[i][n] = b[i];
	}
	printf("Расширенная матрица:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf(" %f", ab[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (ab[i][i] == 0)
		{
			for (int i = 0; i < n; i++)
				free(ab[i]);
			free(ab);
			printf("Решений нет или их бесконечное множество. Коэффициентов нет.");
			return 0;
		}

		for (int j = n; j >= 0; j--)
		{
			ab[i][j] /= ab[i][i];

			for (int k = i + 1; k < n; k++)
			{
				ab[k][j] -= ab[i][j] * ab[k][i];
			}
		}
	}

	printf("Матрица с единичной диагональю:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf(" %f", ab[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = n - 1; i >= 0; i--)
	{
		x[i] = ab[i][n];
		for (int j = n - 1; j > i; j--)
		{
			x[i] -= ab[i][j] * x[j];
		}
	}
	printf("\nВектор коэффициентов:\n");
	for (int j = 0; j < n; j++)
	{
		printf("c[%d] = %f\n", j, x[j]);
	}
	for (int i = 0; i < n; i++)
		free(ab[i]);
	free(ab);
	return 1;
}
int lms(int n, int p, double *x, double *y, double *c) {
	double **a = (double**)malloc((p+1) * sizeof(double*));
	for (int i = 0; i < (p); i++) {
		a[i] = (double*)malloc((p+1) * sizeof(double));
	}
	for (int i = 0; i < (p); i++) {
		for (int k = 0; k < (p); k++) {
			a[i][k] = 0;
			for (int l = 0; l < n; l++) {
				a[i][k] += pow(x[l], (k + i));
			}
		}
	}
	double *b = (double*)malloc((p+1) * sizeof(double));
	for (int i = 0; i < (p); i++) {
		b[i] = 0;
		for (int l = 0; l < n; l++) {
			b[i] += y[l] * pow(x[l], i);
		}
	}
	int result;
	if (GaussianElimination(p, a, b, c)) {
		result = 1;
	}
	else
		result = 0;

	for (int i = 0; i < (p); i++)
		free(a[i]);
	free(a);
	free(b);
	return result;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int n, p;
	double *x, *y, *c;
	printf("Количество узлов: ");
	scanf("%d", &n);
	printf("Порядок полинома: ");
	scanf("%d", &p);
	p += 1;
	x = (double*)malloc(n * sizeof(double));
	y = (double*)malloc(n * sizeof(double));
	c = (double*)malloc(p * sizeof(double));
	printf("Вдите узлы :\n");
	for (int i = 0; i < n; ++i) {
		printf("\nx%d=", (i+1));
		scanf("%lf", &x[i]);
		printf("\ny%d=", (i+1));
		scanf("%lf", &y[i]);
	}
	lms(n, p, x, y, c);
	free(x);
	free(y);
	free(c);
	return 0;
}