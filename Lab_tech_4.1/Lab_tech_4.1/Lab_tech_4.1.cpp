

#include "pch.h"
#include <iostream>
using namespace std;
int m (int n);
int g(int n) {
	if (n > 1) {
		int sum = n;
		n = n - 1;
		sum = sum*m(n);
		return sum;
	}
	else {
		return n;
	}
}
int m(int n) {
	if (n > 1) {
		int sum = n;
		n = n - 1;
		sum = sum*g(n);
		return sum;
	}
	else {
		return n;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Напишите число для вычисления факториала\n";
	int n,sum=0;
	cin >> n;
	cout<<g(n);
	system("pause");
	return 0;
}

