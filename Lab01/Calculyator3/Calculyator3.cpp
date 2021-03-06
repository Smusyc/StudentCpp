#include "pch.h"
#include<iostream>
#include<cmath>
#include<locale>

using namespace std;
struct expr_elem {
	char type;
	double value;
	unsigned char varname;
	char op;
};
typedef struct expr_elem expression_item;
expression_item expression_item_double(double x) {
	expression_item result;
	result.value = x;
	result.type = 1;
	return result;
}
expression_item expression_item_variable(unsigned char var) {
	expression_item result;
	result.varname = var;
	result.type = 2;
	return result;
}
expression_item expression_item_operator(char op) {
	expression_item result;
	result.op = op;
	result.type = 3;
	return result;
}
int count_variables(expression_item *expr, int lenght) {
	int i;
	char* flags = new char[256];
	for (i = 0; i < 256; ++i) {
		flags[i] = 0;
	}
	for (i = 0; i < lenght; ++i) {
		if (expr[i].type == 2) {
			flags[expr[i].varname] = 1;
		}
	}
	int p = 0;
	for (i = 0; i < 256; ++i) {
		if (flags[i] != 0) {
			++p;
		}
	}
	delete[]flags;
	return p;
}
struct _charstack {
	char *p;
	int i;
};

typedef struct _charstack charstack;

charstack cs_create(int size) {
	charstack result;
	result.i = 0;
	result.p = new char[size];
	return result;
}

void cs_remove(charstack * cs) {
	delete[]cs->p;
}

void cs_push(charstack *cs, char value) {
	cs->p[cs->i] = value;
	cs->i += 1;
}

char cs_pop(charstack *cs) {
	char cur = cs->p[cs->i - 1];
	cs->i -= 1;
	return cur;
}

char cs_front(charstack *cs) {
	return cs->p[cs->i - 1];
}

int cs_size(charstack *cs) {
	return cs->i;
}




void fill_stack(charstack *cs) {
	int j;
	for (j = 0; j < 10; ++j) {
		cs_push(cs, j + 50);
	}
}
struct _floatstack {
	float* p;
	int i;
};

typedef struct _floatstack floatstack;

 
void fs_remove(floatstack * fs) {
	delete[] fs->p;
}
bool is_operator(char oper) {
	switch (oper) {
	case'*':case'/':case'&':case'^':case'%':case'#':case'+':case'-':
		return true;
	default:
		return false;
	}
}
int strlen(char* string) {
	int i = 0;
	while (string[i] != 0) {
		++i;
	}
	return i;
}
void fs_push(floatstack *fs, float value) {
	fs->p[fs->i] = value;
	fs->i += 1;
}

float fs_pop(floatstack *fs) {
	float cur = fs->p[fs->i - 1];
	fs->i -= 1;
	return cur;
}

float fs_front(floatstack *fs) {
	return fs->p[fs->i - 1];
}

int fs_size(floatstack *fs) {
	return fs->i;
}
bool brackets(char* str, int lenght) {
	int c = 0;
	int l = 0;
	int n = 0;
	int m = 0;
	int k = 0;
	bool ch = true;
	bool r = true;
	for (int i = 0; i <= lenght; ++i) {
		if (str[i] == '(') {
			--c;
			ch = false;
		}
		if (str[i] == ')') {
			++l;
			k = i;
			while ((str[k] != '(') || (k > 0)) {
				--k;
			}
			if (str[k] == '(') {
				ch = true;
				n = k;
			}

		}
		if (i - n >= 3) {
			r = true;;
		}
		else {
			r = false;
		}
	}
	if ((ch) && ((c + l) == 0) && (r)) {
		ch = false;
		return ch;
	}
	else {
		ch = true;
		return ch;
	}
}

int preor(char x) {
	switch (x) {
	case'+':case'-':
		return 1;
	case'*':case'/':case'&':case'^':case'%':case'#':
		return 2;
	case'$':
		return 3;
	default:
		return 0;
	}
}
void resolve_variables(expression_item *expr, int lenght) {
	int i;
	int count_var = count_variables(expr, lenght);
	char* names_of_var = new char[count_var];
	float* value_of_var = new float[count_var];
	int lenght_var = 0;
	for (i = 0; i < lenght; ++i) {
		if (expr[i].type == 2) {
			int k;
			for (k = 0; k < lenght_var; ++k) {
				if (expr[i].varname == names_of_var[k]) {
					expr[i].value = value_of_var[k];
					break;
				}
			}
			if (k == lenght_var) {
				cout << "Value of variable" << expr[i].varname << "=";
				cin >> expr[i].value;
				names_of_var[lenght_var] = expr[i].varname;
				value_of_var[lenght_var] = expr[i].value;
			}
			expr[i].type = 1;
		}
	}
	delete[]names_of_var;
	delete[]value_of_var;
}
char* readstr() {
	char*memory = new char[400];
	cin.getline(memory, 400);
	return memory;
}
/*expression_item expr[3];
expr[0] = expression_item_double(5);
expr[1] = expression_item_variable('x');
expr[2] = expression_item_operator('+');
printf("%d", sizeof(expression_item));
printf("%d", sizeof(double));*/
void polish(char* str, int* lenght, expression_item**g) {
	int i = 0;
	int p = 0;
	int k = 0;
	int flag = 0;
	float value;
	if (brackets(str, strlen(str))) {
		cout << "Error of brackets";
		return;
	}
	expression_item* unity_massiv = new expression_item[strlen(str)];
	charstack char_stack = cs_create(strlen(str));
	char value_cs_pop;
	char* cash = new char[30];
	while (str[i] != 0) {
		if ((str[i] == '+' || str[i] == '/' || str[i] == '*' || str[i] == '#' || str[i] == '&' || str[i] == '^' || str[i] == '%') && (str[i + 1] == '+' || str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '%' || str[i + 1] == '&' || str[i + 1] == '^')) {
			cout << "Error of writing";
			return;
		}
		if ((str[i + 1] == '-') && (str[i] == '-') && (str[i + 2] == '-')) {
			cout << "Error of writeng";
			return;
		}
		if (('0' <= str[i] && str[i] <= '9') || str[i] == '.') {

			while (('0' <= str[i] && str[i] <= '9' || str[i] == '.') && (str[i] != 0)) {
				cash[p] = str[i];
				++p;
				++i;
			}
			cash[p] = 0;
			--i;
			if (cash[0] == '.') {
				cout << "Error of number";
				return;
			}
			value = atof(cash);
			unity_massiv[k++] = expression_item_double(value);
			p = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			unity_massiv[k++] = expression_item_variable(str[i]);
		}

		else if (str[i] == '(') {
			cs_push(&char_stack, '(');
		}
		else if (is_operator(str[i])) {
			if ((str[i] == '-') && ('0' > str[i - 1] || str[i - 1] > '9') && (('0' <= str[i + 1] && str[i + 1] <= '9') || (str[i + 1] == '('))) {
				cs_push(&char_stack, '$');
			}
			else {
				while ((cs_size(&char_stack) > 0) && (preor(str[i]) <= preor(cs_front(&char_stack)))) {
					unity_massiv[k++] = expression_item_operator(cs_pop(&char_stack));
				}
				cs_push(&char_stack, str[i]);
			}
		}
		else if (str[i] == ')') {
			while ((cs_size(&char_stack) > 0) && ((value_cs_pop = cs_pop(&char_stack)) != '(')) {
				unity_massiv[k++] = expression_item_operator(value_cs_pop);
			}
			if (value_cs_pop != '(') {
				cout << "Error of braces";
				return;
			}
		}
		++i;
	}
	while (cs_size(&char_stack) > 0) {
		unity_massiv[k++] = expression_item_operator((cs_pop(&char_stack)));
	}
	*lenght = k;
	*g = unity_massiv;
	return;
}
float calculate(expression_item* expr, int lenght) {
	int i = 0;
	float op1;
	float op2;
	float clone;
	floatstack fs = fs_create(lenght);
	expression_item h;
	for (i; i < lenght; ++i) {
		h = expr[i];
		if (expr[i].type == 1) {
			fs_push(&fs, expr[i].value);
		}
		else if (expr[i].type == 3) {
			switch (expr[i].op) {
			case'+':
				fs_push(&fs, fs_pop(&fs) + fs_pop(&fs));
				break;
			case'-':
				fs_push(&fs, -fs_pop(&fs) + fs_pop(&fs));
				break;
			case'*':
				fs_push(&fs, fs_pop(&fs)*fs_pop(&fs));
				break;
			case'/':
					fs_push(&fs, (1 / fs_pop(&fs)) * fs_pop(&fs));
				break;
			case'%':
				op2 = fs_pop(&fs);
				op1 = fs_pop(&fs);
				fs_push(&fs, (float)(((int)op1) % ((int)op2)));
				break;
			case'&':
				op2 = fs_pop(&fs);
				op1 = fs_pop(&fs);
				fs_push(&fs, log(op1) / log(op2));
				break;
			case'#':
				clone = 1 / fs_pop(&fs);
				fs_push(&fs, pow(fs_pop(&fs), clone));
				break;
			case'^':
				clone = fs_pop(&fs);
				fs_push(&fs, pow(fs_pop(&fs), clone));
				break;
			case'$':
				fs_push(&fs, (-1)*fs_pop(&fs));
			}
		}
	}

	float result;
	result = fs_pop(&fs);
	fs_remove(&fs);
	return result;
}


void delete_expr(expression_item* expr) {
	delete[]expr;
	//todo написать в соотв с выделением памяти под expr в polish
}
int main() {
	cout << "Enter your expression\n";
	int status = 0;
	char* expr = readstr();
	int expr_lenght;
	expression_item* expression;
	polish(expr, &expr_lenght, &expression);
	if (expr_lenght == 0) {
		status = 1;
		cout << "Error of expression.";
		return 1;
	}
	else {
		resolve_variables(expression, expr_lenght);
		float result = calculate(expression, expr_lenght);
		cout << "Your result=" << result;
		delete_expr(expression);
	}
	delete[] expr;
	return status;


	/* 
	int* array = new int[10];
	array[3];
	*(array + 3 * (sizeof(int)))
	*/
	
}