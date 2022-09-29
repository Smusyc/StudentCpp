// GausLagranj.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#pragma warning (disable: 4996)
using namespace std;

int GaussianElimination(const int n, double** a, double* b, double* x)
{//все n поменять на P и все x поменять на c
	FILE *myfile = fopen("C:/User/yacov/source/repos/GausLagranj/File_Curs_1_Result", "w");
	double** ab = (double**)malloc(n * sizeof(double*));

	for (int i = 0; i < n; i++)
	{
		ab[i] = (double*)malloc((n + 1) * sizeof(double));

		for (int j = 0; j < n; j++)
			ab[i][j] = a[i][j];

		ab[i][n] = b[i];
	}
	printf("Расширенная матрица:\n");
	fprintf(myfile,"Расширенная матрица:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf(" %f", ab[i][j]);
			fprintf(myfile," %f", ab[i][j]);
		}
		printf("\n");
		fprintf(myfile,"\n");
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
			printf("Решений нет или их бесконечное множество.");
			fprintf(myfile,"Решений нет или их бесконечное множество.");
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
			fprintf(myfile," %f", ab[i][j]);
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
	printf("Вектор решения:\n");
	fprintf(myfile,"Вектор решения:\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %f", x[i]);
		fprintf(myfile," %f", x[i]);
	}
	printf("\n");
	fprintf(myfile,"\n");
	for (int i = 0; i < n; i++)
		free(ab[i]);
	free(ab);

	return 1;
}


int lms(int n, int p, double *x, double *y, double *c) {

	//иммитация аппроксимируемой функции
	/*double* e = (double*)malloc(n*sizeof(double));
	double tmp1 = 0,tmp2=1;
	int o = p,k=0;
	for (int l = 0; l < n;l++) {
		for (int i = 0; i < p; ++i) {
			o -= i;
			for (k; k < o; ++k) {
				tmp2 *= x[l];
			}
			tmp1 += tmp2;
			tmp2 = 1;
		}
		e[l] = (y[l]-tmp1)*(y[l] - tmp1);
		tmp1 = 0;
	}*/
	double **a = (double**)malloc((p) * sizeof(double*));
	for (int i = 0; i < (p); i++) {
		a[i] = (double*)malloc((p) * sizeof(double));
	}
	for (int i = 0; i < (p); i++) {
		for (int k = 0; k < (p); k++) {
			a[i][k] = 0;
			for (int l = 0; l < n; l++) {
				a[i][k] += pow(x[l], (k + i));
			}
		}
	}
	double *b = (double*)malloc((p) * sizeof(double));
	for (int i = 0; i < (p); i++) {
		b[i] = 0;
		for (int l = 0; l < n; l++) {
			b[i] += y[l] * pow(x[l], i);
		}
	}

	GaussianElimination(p, a, b, c);

	for (int i = 0; i < (p); i++)
		free(a[i]);
	free(a);
	free(b);
	return 1;
}











/*
int mnk(int n2, int n, double** pts, double* b, double* x)
{
	//матрица хранящая неизвестные при нужных нам коэффициентах
	double** linSys = (double**)malloc((n+1) * sizeof(double*));

	for (int i = 0; i < n; i++)
	{
		linSys[i] = (double*)malloc((n + 1) * sizeof(double));

		for (int j = 0; j < n; j++)
			linSys[i][j] = pts[i][j];

		linSys[i][n] = b[i];
	}

	double tmp = 0;
	double* subsid = (double*)malloc((3 * n + 2) * sizeof(double));//почему 3n + 2? да потому что http://mathhelpplanet.com/static.php?p=onlayn - mnk - i - regressionniy - analiz
	for (int i = 0; i < 2 * n + 1; i++)//этот цикл формирует первую половину (точнее 2/3) списка величин x^0 x^1...x^2n + 1
	{
		for (int j = 0; j < n2; j++)
		{
			tmp += pow(pts[j][0], i);
		}
		subsid[i] = tmp;
		tmp = 0;
	}
	for (int i = 2 * n + 1; i < 3 * n + 2; i++)//этот цикл формирует вторую половину  списка величин x^0*y x^1*y...x^n*y
	{
		for (int j = 0; j < n2; j++)
		{
			tmp += pow(pts[j][0], i - 2 * n - 1)*pts[j][1];
		}
		subsid[i] = tmp;
		tmp = 0;
	}
	//тут уже идёт формирование СЛАУ получаем матрицу linSys
	//a1*Ex^n      +  a2*Ex^n  -  1   +  ...  +  an*Ex^0=Eyx^0
	//a1*Ex^n  +  1  +  a2*Ex^n       +  ...  +  an*Ex^1=Eyx^1
	//  ...            ...         ...       ...
	//a1*Ex^2n     +  a2*Ex^2n  -  1  +  ...  +  an*Ex^n=Eyx^n
	//Будем решать СЛАУ в виде A*x=b
	//в моем случае linSys*x=b
	double*b2 = (double*)malloc((n + 1) * sizeof(double));
	for (int i = 0; i < n + 1; i++)
	{
		linSys[i] = (double*)malloc((n + 1) * sizeof(double));
		b2[i] = subsid[2 * n + 1 + i];
		for (int j = 0; j < n + 1; j++)
		{
			linSys[i][j] = subsid[n + i - j];
		}

	}
	//это решает СЛАУ и пишет результ в x
	GaussianElimination(n, linSys, b2, x);
	return 1;
}

double ** getData(int n) {
	double a = 0.2; double b = 0.95;
	double **f;
	f = new double*[2];
	f[0] = new double[n];
	f[1] = new double[n];
	double x;
	double step = (b - a) / (n - 1);
	for (int i = 0; i < n; i++) {
		x = a + step * i;
		f[0][i] = x;
		f[1][i] = -pow((x * x), 1. / 3) - pow((1 - (x * x)), 1. / 3);
	}
	return f;
}
// Вычисление коэффициентов аппроксимирующей прямой
void getApprox(double **x, double *a, double *b, int n) {
	double sumx = 0;
	double sumy = 0;
	double sumx2 = 0;
	double sumxy = 0;
	for (int i = 0; i < n; i++) {
		sumx += x[0][i];
		sumy += x[1][i];
		sumx2 += x[0][i] * x[0][i];
		sumxy += x[0][i] * x[1][i];
	}
	*a = (n*sumxy - (sumx*sumy)) / (n*sumx2 - sumx * sumx);
	*b = (sumy - *a*sumx) / n;
	return;
}
*/
/*
int JordanMethod(const int n, double** a, double* b, double* x)
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
			printf("%f", ab[i][j]);
			printf(" ");
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
			return 0;
		}

		for (int j = n; j >= 0; j--)
		{
			ab[i][j] /= ab[i][i];

			for (int k = 0; k < n; k++)
			{
				if (k == i) continue;
				ab[k][j] -= ab[i][j] * ab[k][i];
			}
		}
	}

	printf("Матрица со всеми преобразованиями:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf("%f", ab[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		x[i] = ab[i][n];
	}

	for (int i = 0; i < n; i++)
		free(ab[i]);
	free(ab);

	return 1;
}
*/




int main()
{
	setlocale(LC_ALL, "Rus");
		printf("Введите количество строк в квадратной матрице.\n");
		int lines = 0;
		scanf("%d", &lines, sizeof(int));
		FILE *myfile = fopen("C:/User/yacov/source/repos/GausLagranj/File_Curs_1.txt", "r");
		char str[200];
		double** a = (double**)malloc(lines * sizeof(double*));
		double* b = (double*)malloc(lines * sizeof(double));
		for (int i = 0; i < lines; i++) {
			a[i] = (double*)malloc(lines * sizeof(double));
		}
		
		int tmp = 0,place_c = 0;
		char *buffer = (char*)malloc(10 * sizeof(char));
		for (int y = 0; y < lines;++y) {
			if (myfile == NULL) perror("Ошибка открытия файла");
			else{
			fgets(str, 200, myfile);
			while (str[tmp] != '\0' || str[tmp] != '\n') {
				if (str[tmp] != ' ') {
					buffer += str[tmp];
				}
				else {
					if (place_c == lines) {
						place_c = 0;
						
					}
					a[y][place_c] = atof(buffer);
					++place_c;
					memset(buffer, '\0', sizeof(buffer));
				}
				tmp++;
			}
			tmp = 0;
		}
		fgets(str, 200, myfile);
		if (str[0] == '\n') {
			place_c = 0;
			fgets(str, 80, myfile);
			while (str[tmp] != '\0' || str[tmp] != '\n') {
				if (str[tmp] != ' ') {
					buffer += str[tmp];
				}
				else {
					if (place_c == lines) {
						place_c = 0;

					}
					b[place_c] = atof(buffer);
					place_c++;
				}
				tmp++;
			}
			tmp = 0;
		}
		}
		fclose(myfile);
		
		/*double** a = (double**)malloc(lines * sizeof(double*));
		printf("\nВведите значение\n");
		for (int i = 0; i < lines; i++) {
			a[i] = (double*)malloc(lines * sizeof(double));
		}
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < lines; j++) {
				printf("\na[%d][%d]=", i, j);
				scanf("%lf", &a[i][j], sizeof(double));
			}
		}
		double* b = (double*)malloc(lines * sizeof(double));
		printf("\nВведите значение\n");
		for (int j = 0; j < lines; j++) {
			printf("\nb[%d]=", j);
			scanf("%lf", &b[j], sizeof(double));
		}*/
		double* x = (double*)malloc(lines * sizeof(double));
		for (int i = 0; i < lines; i++)
			x[i] = 0;

		printf("Метод Гаусса.\n");
		GaussianElimination(lines, a, b, x);
		free(x);
		for (int i = 0; i < lines; ++i) {
			free(a[i]);
		}
		free(a);
		printf("\n\n\n");
		int p, n;
		printf("Метод НК.\n\nВведите порядок полинома: ");
		scanf("%d", &p, sizeof(int));
		p += 1;
		printf("\n\nВведите количество узловых точек: ");
		scanf("%d", &n, sizeof(int));
		double *x2 = (double*)malloc(n * sizeof(double));
		double *y = (double*)malloc(n * sizeof(double));
		double *c = (double*)malloc((p) * sizeof(double));

		/*
		for (int k = 0; k < n; k++) {
			printf("\nВведите x%d: ", k);
			scanf("%lf", &x2[k], sizeof(double));
			printf("\nВведите y%d: ", k);
			scanf("%lf", &y[k], sizeof(double));
			}
			*/

		//pltc
		free(myfile);
		FILE *myfile2 = fopen("C:/User/yacov/source/repos/GausLagranj/File_Curs_2", "r");
		char str2[100];
			fgets(str, 200, myfile2);
			fgets(str2, 200, myfile2);
			tmp = 0;
			while (str[tmp] != '\0' || str[tmp] != '\n') {
				if (str[tmp] != ' ') {
					buffer += str[tmp];
				}
				else {
					if (tmp== n) {
						break;

					}
						x2[tmp] = atof(buffer);
						tmp++;
						memset(buffer, '\0', sizeof(buffer));
				}
			}
			tmp = 0;
			while (str2[tmp] != '\0' || str2[tmp] != '\n') {
				if (str2[tmp] != ' ') {
					buffer += str2[tmp];
				}
				else {
					if (tmp == n) {
						break;

					}
						y[tmp] = atof(buffer);
						tmp++;
						memset(buffer, '\0', sizeof(buffer));
				}
			}
			fclose(myfile2);
			free(myfile2);
		lms(n, p, x2, y, c);
		free(y);
		free(x2);
		free(c);
	
}




