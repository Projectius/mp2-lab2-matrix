// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
void inputMatrix(TDynamicMatrix<int>& m) {
	cout << "Введите все элементы матрицы" << endl;
	bool invalidinp = 1;
	do {
		cin >> m;
		invalidinp = cin.fail();
			if (invalidinp) {
				cout << "Неправильный ввод, повторите ввод заново"<<endl;
				cin.clear();
			}
		cin.ignore(INT_MAX, '\n');
	} while (invalidinp);
	cout << "Введённая матрица: " << endl;
	cout << m;
}

void inputInt(int& n) {
	cout << "Введите номер команды" << endl<<"> ";
	bool invalidinp = 1;
	do {
		cin >> n;
		invalidinp = cin.fail();
		if (invalidinp) {
			cout << invalidinp<< "Неправильный ввод, повторите ввод заново\n";
			cin.clear();
		}
		cin.ignore(INT_MAX, '\n');
	} while (invalidinp);
}

void main()
{
	//TDynamicMatrix<int> a(5), b(5), c(5);
	//int i, j;

	setlocale(LC_ALL, "Russian");
	int msz = 1;
	
	while (true) {
		cout << "Начало\n";
		bool back = 0;
		do {
			cout << "Введите размер учавствующих в операциях матриц:" << endl;
			cin >> msz;
			if (cin.fail())
				cin.clear();
			cin.ignore(INT_MAX, '\n');
		} while (!((0 < msz) && (msz < MAX_MATRIX_SIZE)));
		TDynamicMatrix<int> a(msz), b(msz);
		cout << "Матрица А\n";
		inputMatrix(a);
		cout << endl << "Выберете действие с введённой матрицей А:" << endl <<
			"1) Умножить на матрицу" << endl <<
			"2) Прибавить матрицу" << endl <<
			"3) Вычесть матрицу" << endl <<
			"4) Вернуться к вводу матрицы A" << endl;
		int op = 0;

		do {
			
			inputInt(op);
			cout << endl;
			switch (op) {
			case 1:
				inputMatrix(b);
				cout << "\nA * B =" << endl << a * b << endl;
				break;
			case 2:
				inputMatrix(b);
				cout << "\nA + B =" << endl << a + b << endl;
				break;
			case 3:
				inputMatrix(b);
				cout << "\nA - B =" << endl << a - b << endl;
				break;
			case 4:
				back = 1;
				break;
			default:
				cout << "Команда не распознана\n";
				break;
			}
			if (back) {

				break;
			}
		} while (true);
	}
	/*cout << "Тестирование класс работы с матрицами"
		<< endl;
	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	c = a + b;
	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;*/
}
//---------------------------------------------------------------------------
