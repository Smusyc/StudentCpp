#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#pragma warning (disable: 4996)
using namespace std;

int slau(const int n, double** a, double* b, double* x) {
	FILE *myfile = fopen("C:/Users/yacov/source/repos/File_Curs_1_Result.txt", "w");
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


/*
int slau(const int n, double** a, double* b, double* x)
{//все n поменять на P и все x поменять на c
	FILE *myfile = fopen("C:/Users/yacov/source/repos/File_Curs_1_Result.txt", "w");
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
		if (ab[i][i] == 0)
		{
			for (int i = 0; i < n; i++)
				free(ab[i]);
			free(ab);
			printf("Решений нет или их бесконечное множество.\n");
			fprintf(myfile, "Решений нет или их бесконечное множество.");
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
	fprintf(myfile,"Матрица с единичной диагональю:\n");
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
	fprintf(myfile,"\nВектор решений:\n");
	for (int i = 0; i < n; i++)
	{
		printf("x[%d] = %f\n", i + 1, x[i]);
		fprintf(myfile, "%f\n", x[i]);
	}
	for (int i = 0; i < n; i++)
		free(ab[i]);
	free(ab);

	return 1;
}*/
void main(void)
{
	setlocale(LC_ALL, "Rus");
	int n, i, j;
	double **a, *b, *x, temp = 0.0;
	FILE *f;
	printf("Порядок системы: ");
	scanf("%d", &n);
	f = fopen("C:/Users/yacov/source/repos/File_Curs_1.txt", "r");
	a = (double**)malloc(n * sizeof(double*));
	for (i = 0; i < n; i++)
	{
		a[i] = (double*)malloc(n * sizeof(double));
		for (j = 0; j < n; j++)
			fscanf(f, "%lf", &a[i][j]);
	}
	b = (double*)malloc(n * sizeof(double));
	for (i = 0; i < n; i++)
		fscanf(f, "%lf", &b[i]);
	fclose(f);
	x = (double*)malloc(n * sizeof(double));
	slau(n, a, b, x);
	
	for (i = 0; i < n; i++)
		free(a[i]);
	free(a);
	free(b);
	free(x);
}