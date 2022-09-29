#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#pragma warning (disable: 4996)
using namespace std;
int slau(const int n, double** a, double* b, double* x) {
	FILE *myfile = fopen("C:/Users/yacov/source/repos/File_Curs_2_Result.txt", "w");
	double** ab = (double**)malloc(n * sizeof(double*));

	for (int i = 0; i < n; i++)
	{
		ab[i] = (double*)malloc((n + 1) * sizeof(double));
		for (int j = 0; j < n; j++)
			ab[i][j] = a[i][j];
		ab[i][n] = b[i];
	}
	printf("Расширенная матрица:\n");
	fprintf(myfile, "Расширенная матрица:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf(" %f", ab[i][j]);
			fprintf(myfile, " %f", ab[i][j]);
		}
		printf("\n");
		fprintf(myfile, "\n");
	}
	printf("\n");
	fprintf(myfile, "\n");
	for (int i = 0; i < n; i++)
	{
		if (fabs(ab[i][i]) < 1e-6)
		{
			for (int i = 0; i < n; i++)
				free(ab[i]);
			free(ab);
			printf("Система не может быть решена данным методом.\n");
			fprintf(myfile, "Система не может быть решена данным методом.");
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
	fprintf(myfile, "Матрица с единичной диагональю:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf(" %f", ab[i][j]);
			fprintf(myfile, " %f", ab[i][j]);
		}
		printf("\n");
		fprintf(myfile, "\n");
	}
	printf("\n");
	fprintf(myfile, "\n");

	for (int i = n - 1; i >= 0; i--)
	{
		x[i] = ab[i][n];
		for (int j = n - 1; j > i; j--)
		{
			x[i] -= ab[i][j] * x[j];
		}
	}
	printf("\nВектор решений:\n");
	fprintf(myfile, "\nВектор решений:\n");
	for (int i = 0; i < n; i++)
	{
		printf("x[%d] = %f\n", i + 1, x[i]);
		fprintf(myfile, "%f\n", x[i]);
	}
	for (int i = 0; i < n; i++)
		free(ab[i]);
	free(ab);
	return 1;
}

int lms(int n, int p, double *x, double *y, double *c) {

	double **a = (double**)malloc((p+1) * sizeof(double*));
	for (int i = 0; i <= (p); i++) {
		a[i] = (double*)malloc((p+1) * sizeof(double));
	}
	for (int i = 0; i <= (p); i++) {
		for (int k = 0; k <= (p); k++) {
			a[i][k] = 0;
			for (int l = 0; l < n; l++) {
				a[i][k] += pow(x[l], (k + i));
			}
		}
	}
	double *b = (double*)malloc((p+1) * sizeof(double));
	for (int i = 0; i <= (p); i++) {
		b[i] = 0;
		for (int l = 0; l < n; l++) {
			b[i] += y[l] * pow(x[l], i);
		}
	}
	int result;
	if (slau(p+1, a, b, c)) {
		result = 1;
	}
	else
		result= 0;

	for (int i = 0; i <= p; i++)
		free(a[i]);
	free(a);
	free(b);
	return result;
}
int main()
{
	setlocale(LC_ALL,"Rus");
	int n, p;
	double *x, *y, *c;
	FILE *f;
	printf("Количество узлов: ");
	scanf("%d", &n);
	printf("Порядок полинома: ");
	scanf("%d", &p);
	f = fopen("C:/Users/yacov/source/repos/File_Curs_2.txt", "r");
	x = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		fscanf(f, "%lf", &x[i]);
	y = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		fscanf(f, "%lf", &y[i]);
	fclose(f);
	c = (double*)malloc(p+1 * sizeof(double));
	fclose(f);
	lms(n, p, x, y, c);
	free(x);
	free(y);
	return 0;
}