#include "pch.h" 
#include <iostream> 
using namespace std;
int doska[8][8];
void reset(int i, int j)
{
	for (int x = 0; x < 8; ++x)
	{
		--doska[x][j];
		--doska[i][x];
		int k;
		k = j - i + x;
		if (k >= 0 && k < 8)
			--doska[x][k];
		k = j + i - x;
		if (k >= 0 && k < 8)
			--doska[x][k];
	}
	doska[i][j] = 0;
}//обнуление по троектории ферзя

void set(int i, int j)
{
	for (int x = 0; x < 8; ++x)
	{
		++doska[x][j];
		++doska[i][x];
		int k;
		k = j - i + x;
		if (k >= 0 && k < 8)
			++doska[x][k];
		k = j + i - x;
		if (k >= 0 && k < 8)
			++doska[x][k];
	}
	doska[i][j] = -1;//заполнение доски по траектории ферзя
}

bool postan(int i)
{
	bool result = false;
	for (int j = 0; j < 8; ++j)
	{
		if (doska[i][j] == 0)
		{
			set(i, j);
			if (i == 7)
				result = true;
			else
			{
				if (!(result = postan(i + 1)))//рекурсия по строкам, если постановка не удалась
					reset(i, j);
			}
		}
		if (result)//верно, когда постановка была произведена во всех строках и при этом успешно
			break;
	}
	return result;
}//расставляет фигуры до тех пор пока
int main()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			doska[i][j] = 0;//заполнение пустотами
	postan(0);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (doska[i][j] == -1)
				cout<< "? ";//место для фигуры
			else
				cout<< "X ";//места не для фигур
		}
		cout << endl;
	}
	system("pause");
	return 0;
}	
