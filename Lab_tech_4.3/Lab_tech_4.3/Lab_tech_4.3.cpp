#include "pch.h"
#include <iostream>
using namespace std;
float m(float x,int shary);

float g(float x,int shary){
	float result;
	if (x != 0) {
		if (shary < 128) {
			shary += 1;

			if (shary == 0) {
				result= x / (pow(x, 2) + ((shary * 2) / m(x, shary)));
			}
			else {
				result= (pow(x, 2) + ((shary * 2) / m(x, shary)));
			}
		}
		if (shary == 128) {
			result= (pow(x, 2) + ((shary * 2) / pow(x,2)));
		}
	}
	else {
		cout << "Ошибка";
		return 0;
	}
	return result;
}
float m(float x, int shary) {
	float result;
	if (x != 0) {
		if (shary < 128) {
			shary += 1;
			result = (pow(x, 2) + ((shary * 2) / g(x, shary)));
		}
		if (shary == 128) {
			result = (pow(x, 2) + ((shary * 2) / pow(x, 2)));
		}
	}
	else {
		cout << "Ошибка";
		return 0;
	}
	return result;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Напишите число не равное 0\n";
	float x;
	int shary = -1;
	cin >> x;
	cout << "Ваше число: ";
	cout << g(x,shary);
	system("pause");
	return 0;
}

