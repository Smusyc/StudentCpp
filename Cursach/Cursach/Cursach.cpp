#include "pch.h"
#include <iostream>
#include<string>
#include"string.h"
#include<vector>
#include<tchar.h>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<locale>
using namespace std;
template<class TKey, class TValue>
class Collection {
public:
	class Unit {
	public:
		vector<TKey> vector_key;
		vector<TValue> vector_value;
		Unit(TKey newKey, TValue newValue) {
			vector_key.push_back(newKey);
			vector_value.push_back(newValue);
		}

	};
	bool flag = true;
	vector<Unit> List;
	void Add(TKey key, TValue value) {
		Unit add(key, value);
		List.push_back(add);
	}
	void DeleteTK(TKey key) {
		int i = 0;
		if (Get_Key(key, i, flag)) {
			List.erase(List.begin() + i);
			cout << "\nПеревод для [" << key << "]  удалён\n";
		}
	}
	void DeleteTV(TValue value) {
		int i = 0;
		if (Get_Value(value, i, flag)) {
			List.erase(List.begin() + i);
			cout << "\nПеревод для [" << value << "]  удалён\n";
		}
	}
	void DeleteK_V(TKey key, TValue value) {
		int i = 0, Lenght_List_value;
		if (Get_Key(key, i, flag)) {
			Lenght_List_value = List[i].vector_value.size();
			for (int j = 0; j < Lenght_List_value; ++j) {
				if (value == List[i].vector_value[j]) {
					List[i].vector_value.erase(List[i].vector_value.begin() + j);
					Lenght_List_value = List[i].vector_value.size();
				}
			}
			cout << "\nПеревод [" << key << " = " << value << "] удалён\n";
		}
	}
	void DeleteV_K(TValue value, TKey key) {
		int i = 0, Lenght_List_key;
		if (Get_Value(value, i, flag)) {
			Lenght_List_key = List[i].vector_key.size();
			for (int j = 0; j < Lenght_List_key; ++j) {
				if (value == List[i].vector_key[j]) {
					List[i].vector_key.erase(List[i].vector_key.begin() + j);
					Lenght_List_key = List[i].vector_key.size();
				}
			}
			cout << "\nПеревод [" << value << " = " << key << "] удалён\n";
		}
	}
	bool Get_Key(TKey key, int &i, bool &vkl) {
		int Lenght_unit = List.size(), Lenght_key, j;
		bool flag_get = false;
		for (i; i < Lenght_unit; i++) {
			Lenght_key = List[i].vector_key.size();
			for (j = 0; j < Lenght_key; j++) {
				if (key == List[i].vector_key[j]) {
					flag_get = true;
					break;
				}
			}
			if (flag_get) {
				break;
			}
		}
		if (!flag_get) {
			if (vkl) {
				cout << "\nНеизвестный ключ";
			}
			return false;
		}
		else {
			return true;
		}
	}
	bool Get_Value(TValue value, int &i, bool &vkl) {
		int Lenght_unit = List.size(), Lenght_value, j;
		bool flag_get = false;
		for (i; i < Lenght_unit; i++) {
			Lenght_value = List[i].vector_value.size();
			for (j = 0; j < Lenght_value; j++) {
				if (value == List[i].vector_value[j]) {
					flag_get = true;
					break;
				}
			}
			if (flag_get) {
				break;
			}
		}
		if (!flag_get) {
			if (vkl) {
				cout << "\nНеизвестный ключ";
			}
			return false;
		}
		else {
			return true;
		}
	}
};
template<class TK, class TV>
class Dictionary {
public:
	bool E_R = true;
	Collection<TK, TV> ListD;
	void AddTranslationK(TK elem_1, TV elem_2, bool vkl) {
		int i = 0, j = 0;
		if (!ListD.Get_Key(elem_1, i, vkl)) {
			ListD.Add(elem_1, elem_2);
		}
		else {
			if (!ListD.Get_Value(elem_2, j, vkl)) {
				ListD.List[i].vector_value.push_back(elem_2);
			}
		}
		if (vkl) {
			cout << "\nПеревод добавлен";
		}
	}
	void AddTranslationV(TV elem_1, TK elem_2, bool vkl) {
		int i = 0, j = 0;
		if (!ListD.Get_Value(elem_1, i, vkl)) {
			ListD.Add(elem_2, elem_1);
		}
		else {
			if (ListD.Get_Key(elem_2, j, vkl)) {
				ListD.List[i].vector_key.push_back(elem_2);
			}
		}
		if (vkl) {
			cout << "\nПеревод добавлен";
		}
	}
	void Add_Key_K(TK elem_1, TK elem_2, bool vkl) {
		int i = 0;
		if (ListD.Get_Key(elem_1, i, vkl)) {
			ListD.List[i].vector_key.push_back(elem_2);
			cout << "\nСиноним [" << elem_2 << "] добавлен к " << elem_1;
		}
	}
	void Add_Key_V(TV elem_1, TV elem_2, bool vkl) {
		int i = 0;
		if (ListD.Get_Value(elem_1, i, vkl)) {
			ListD.List[i].vector_value.push_back(elem_2);
			cout << "\nСиноним [" << elem_2 << "] добавлен к " << elem_1;
		}
	}
	void TranslateK(TK key, bool vkl) {
		int ListD_unit = 0, ListD_lenght, border;
		if (ListD.Get_Key(key, ListD_unit, vkl)) {
			cout << "\n" << key << "--->";
			while (ListD.Get_Key(key, ListD_unit, vkl)) {
				ListD_lenght = ListD.List[ListD_unit].vector_value.size();
				for (int i = 0; i < ListD_lenght; ++i) {
					cout << ListD.List[ListD_unit].vector_value[i] << ", ";
				}
				++ListD_unit;
			}
		}
	}
	void TranslateV(TV value, bool vkl) {
		int ListD_unit = 0, ListD_lenght;
		if (ListD.Get_Value(value, ListD_unit, vkl)) {
			cout << "\n" << value << "--->";
			while (ListD.Get_Value(value, ListD_unit, vkl)) {
				ListD_lenght = ListD.List[ListD_unit].vector_key.size();
				for (int i = 0; i < ListD_lenght; ++i) {
					cout << ListD.List[ListD_unit].vector_key[i] << ", ";
				}
				++ListD_unit;
			}
		}
	}
	void Input() {
		ifstream input;
		string str1, str2;
		input.open("Dictionary.txt", ios_base::in);
		istringstream transf("");
		TK add_key;
		TV add_value;
		bool flag = false;
		while (!input.eof()) {
			getline(input, str1, '=');
			transf = istringstream(str1);
			transf >> add_key;
			getline(input, str2);
			transf = istringstream(str2);
			transf >> add_value;
			AddTranslationK(add_key, add_value, flag);
			str1 = "";
			str2 = "";
		}
	}
	void Output() {
		ofstream output;
		output.open("Dictionary.txt", ios_base::trunc | ios_base::out);
		int Lenght_value, Lenght_key, Lenght_list = ListD.List.size();
		for (int i = 0; i < Lenght_list; ++i) {
			Lenght_value = ListD.List[i].vector_value.size();
			for (int j = 0; j < Lenght_value; ++j) {
				Lenght_key = ListD.List[i].vector_key.size();
				for (int k = 0; k < Lenght_key; ++k) {
					output << ListD.List[i].vector_key[k] << '=' << ListD.List[i].vector_value[j] << endl;
				}
			}
		}
	}
	void Menu() {
		string Command = "";
		bool flag = true, file_flag = false;
		cout << "rev-сменить режим\naddk-дабавить синоним к ключу\naddt-добавить перевод\ntr-перевести\ndlt-удалить ключ и все его значения\ndlkv-удалить одно значение по ключу\n?-помощь\ninc-вложить в словарь\nex-выйти";
		cout << "\n\nВзять словарь из фаила? [yes/no]\n";
		cin >> Command;
		if (Command == "yes") {
			Input();
			file_flag = true;
			cout << "\nФайл подключён";
			Output();
		}
		cout << "\nАнгло-Русский переводчик включен";
		while (Command != "ex") {
			if (Command == "inc") {
				if (!file_flag) {
					Input();
					file_flag = true;
					cout << "\nФайл подключён";
					Output();
					Input();
				}
				else {
					cout << "\nФайл уже потключен";
				}

			}
			if (Command == "?") {
				cout << "rev-сменить режим\naddk-дабавить синоним к ключу\naddt-добавить перевод\ntr-перевести\ndlt-удалить ключ и все его значения\ndlkv-удалить одно значение по ключу\n?-помощь\ninc-вложить в словарь\nex-выйти";
			}
			if (Command == "rev") {
				if (E_R) {
					cout << "\nРусско-Английский переводчик включен";
					E_R = false;
				}
				else {
					cout << "\nАнгло-Русский переводчик включен";
					E_R = true;
				}
			}
			if (E_R) {
				TK per1;
				TV per2;
				cout << "\nВводите команду\n";
				cin >> Command;
				if (Command == "dlt") {
					cout << "Введите ключ перевод которого вы хотите удалить: ";
					cin >> per1;
					ListD.DeleteTK(per1);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "dlkv") {
					cout << "Введите ключ значение которого вы хотите удалить\nКлюч: ";
					cin >> per1;
					cout << "\nЗначение: ";
					cin >> per2;
					ListD.DeleteK_V(per1, per2);
					if (file_flag) {
						Output();
					}
				}
				if (Command == "addt") {
					cout << "\nВведите слово и его перевод\nСлово: ";
					cin >> per1;
					cout << "\nПеревод: ";
					cin >> per2;
					AddTranslationK(per1, per2, flag);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "addk") {
					TK per3;
					cout << "\nНапишите слово и слово, к которому предыдущее слово является синонимом\nДобавка: ";
					cin >> per1;
					cout << "\nЦель: ";
					cin >> per3;
					Add_Key_K(per3, per1, flag);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "tr") {
					cout << "\nВведите слово, перевод которого вы хотите узнать: ";
					cin >> per1;
					TranslateK(per1, flag);
				}
			}
			else {
				TV per1;
				TK per2;
				cout << "\nВводите команду\n";
				cin >> Command;
				if (Command == "addt") {
					cout << "\nВведите слово и его перевод\nСлово: ";
					cin >> per1;
					cout << "\nПеревод: ";
					cin >> per2;
					AddTranslationV(per1, per2, flag);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "addk") {
					TV per3;
					cout << "\nНапишите слово и слово, к которому предыдущее слово является синонимом\nДобавка: ";
					cin >> per1;
					cout << "\nЦель: ";
					cin >> per3;
					Add_Key_V(per3, per1, flag);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "dlt") {
					cout << "Введите ключ перевод которого вы хотите удалить: ";
					cin >> per1;
					ListD.DeleteTV(per1);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "dlkv") {
					cout << "Введите ключ значение которого вы хотите удалить\nКлюч: ";
					cin >> per1;
					cout << "\nЗначение: ";
					cin >> per2;
					ListD.DeleteV_K(per1, per2);
					if (file_flag) {
						Output();
						Input();
					}
				}
				if (Command == "tr") {
					cout << "\nВведите слово, перевод которого вы хотите узнать: ";
					cin >> per1;
					TranslateV(per1, flag);
				}
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(866);
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Dictionary<string, string> Dic;
	Dic.Menu();
	system("pause");
	return 0;
}
