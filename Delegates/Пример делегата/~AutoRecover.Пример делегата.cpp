#include "pch.h"
#include <functional>
#include <iostream>
using namespace std;
int main()
{
	cout << "Введите переменную a\na=";
	float a;
	cin >> a;
	cout << "Введите переменную b\nb=";
	float b;
	cin >> b;
	cout << "Введите знак операхии для a ? b\n";
	char oper;
	cin >> oper;
	float* result;

	switch(oper){
	case'+':
		result=[a,b](float a, float b)->float* {
			return a + b;
		}
	break;
	case'-':
		
	break;
	case'/':

		break;
	case'*':

		break;
	case'%':

		break;
	}
}
