

#include "pch.h"
#include <iostream>
using namespace std;
float m(float n,float sum);
float g(float n, float sum) {
	if (n != 0) {
		sum = 1 / n;
		n = n - 1;
		sum += m(n, sum);
		return sum;
	}
	else {
		return 0;
	}
}
	float m(float n,float sum){
		if (n != 0) {
			sum = 1 / n;
			n = n - 1;
			sum += g(n, sum);
			return sum;
		}
		else {
			return 0;
		}
	}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Напишите число для вычисления факториала\n";
	float n, sum = 0;
	cin >> n;
	cout << g(n,sum);
	system("pause");
	return 0;
}

