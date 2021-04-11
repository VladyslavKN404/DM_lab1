#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define N 8
#define INF 999999
#define INF2 0

int read_matrix(int matr[N][N]) {
	ifstream in("l1-1.txt");
	if (in.is_open())
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				in >> matr[i][j];

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << matr[i][j] << "\t";
			cout << "\n";
		}

		in.close();
		return **matr;
	}
	else
	{
		cout << "Файл не знайдено.";
		return 0;
	}
}

int min_tree(int matr[N][N]) {
	cout << "Пошук Мiнiмального остового дерева за алгоритмом Прима" << endl;
	int weight = 0;
	int no_edge = 0;
	int selected[N];
	int x;
	int y;

	memset(selected, false, sizeof(selected));
	selected[0] = true;

	cout << " Ребро" << " : " << "Вага";
	cout << endl;
	while (no_edge < N - 1) {
		int min = INF;
		x = 0;
		y = 0;

		for (int i = 0; i < N; i++) {
			if (selected[i]) {
				for (int j = 0; j < N; j++) {
					if (!selected[j] && matr[i][j]) {
						if (min > matr[i][j]) {
							min = matr[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		cout << " " << x << " - " << y << " :  " << matr[x][y] << endl;
		weight += matr[x][y];
		selected[y] = true;
		no_edge++;
	}
	cout << "Сумарна вага: " << weight << endl;
	return 0;
}


void main()
{
	setlocale(LC_ALL, "Ukrainian");
	int matr[N][N];
	cout << "Кiлькiсть вершин: " << N << endl;
	cout << "Матриця ваг: " << endl;
	read_matrix(matr);
	min_tree(matr);

	system("pause");
}