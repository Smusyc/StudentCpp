#include"pch.h"
#include<iostream>
using namespace std;
template <class T>
class vector_p
{
public:
	T* _array=NULL;
	int _size;
	int _length;

	vector_p() : _size(10), _length(0) {
		_array = new T[_size];
	}
	int size() {
		return _length;
	}
	void push_back(T value) {
		if (_length + 1 > _size) {
			resize(_size * 2);
		}
		_array[_length++] = value;
		cout << "\n" << _array[_length - 1];
	}
	void erase(int place) {
		size_t new_length = 0;
		for (int i = 0; i < _length; i++)
		{
			if (i==place) continue;
			_array[new_length++] = _array[i];
		}
		_length = new_length;
	}
	T& operator[](int index) {
		return _array[index];
	}
	void resize(unsigned int new_size) {
		_size = new_size;
		_array = static_cast<T*>(realloc(_array, _size * sizeof(T)));
	}
	int begin() {
		int i = 0;
		return i;
	}
};
int main() {
	if (true) {
		vector_p<vector_p<int>> dic;
		vector_p<int> unit;
		int i = 2;
		unit.push_back(1);
		unit.push_back(2);
		unit.push_back(3);
		unit.push_back(4);
		unit.push_back(5);
		unit.push_back(6);
		unit.erase(3);
		cout << unit[1];
		cout << unit[2];
		cout << unit[3];
		cout << unit[4];
		cout << unit[5];
		cout << unit[6];
	}
	system("pause");
	return 0;
}