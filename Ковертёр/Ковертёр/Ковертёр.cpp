#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Сколько у вас денег?\n";
	int k;
	int r;
	int sum;
	cin >> sum;
	r = sum / 100;
	k = sum % 100;
	cout << "ИТОГО: ";
	if ((k==0) && (r== 0)) {
		cout << " ничего не куплено";
	}
	else if (r != 0) {
		if (r % 100 != 11) {
			if ((r % 100 < 12) || (r % 100 > 14)) {
				if ((r % 10 < 2) || (r % 10 > 4)) {
					if (r % 10 == 1) {
						cout << r << " РУБЛЬ ";
					}
					else {
						cout << r << " РУБЛЕЙ ";
					}
				}
				else {
					cout << r << " РУБЛЯ ";
				}
			}
			else {
				cout << r << " РУБЛЕЙ ";
			}
		}
		else {
			cout << r << " РУБЛЕЙ ";
		}
	}
		
		if (k != 0) {
			if (k != 11) {
				if ((12 > k) || (k > 14)) {
					if ((k % 10 < 2) || (k % 10 > 4)) {
						if (k % 10 == 1) {
							cout << k << " КОПЕЙКА ";
						}
						else {
							cout << k << " КОПЕЕК ";
						}
					}
					else {
						cout << k << " КОПЕЕК ";
					}
				}
				else {
					cout << k << " КОПЕЕК ";
				}
			}
			else {
				cout << k << " КОПЕЕК ";
			}
		}
	
	
	return 0;
}