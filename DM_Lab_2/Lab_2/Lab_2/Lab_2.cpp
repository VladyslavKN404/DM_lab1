#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define N 8
#define K 100000

int read_matrix(int matr[N][N]) {
	ifstream in("l2-1.txt");
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

int sum_edges_vertexes(int con_matr[N][N]) {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += con_matr[i][j];
		}
	}
	return sum;
}

int euler(int matr[N][N], int con_matr_[N][N]) {
	int con_matr[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			con_matr[i][j] = con_matr_[i][j];
		}
	}
	int p[K + 1];
	int p1;
	int p2;
	int s = 0;
	int k = sum_edges_vertexes(con_matr) / 2;
	int weight = 0;

	p1 = 0;
	p2 = k + 1;
	p[p1] = s;

	while (p1 >= 0)
	{
		int i, v = p[p1];
		for (i = 0; i < N; ) {
			if (con_matr[v][i] != 0)
			{
				con_matr[v][i] = con_matr[v][i] - 1;
				con_matr[i][v] = con_matr[i][v] - 1;
				p[++p1] = i;
				v = i;
				i = 0;
			}
			else {
				i++;
			}
		}
		if (i >= N) {
			p[--p2] = p[p1--];
		}
	}

	if (p2 > 0)
	{
		cout << "граф не Ейлеровий" << endl;
	}
	else {
		cout << " Ребро : Вага \n";
		for (int i = 0; i < k; i++) {
			cout << " " << p[i] + 1 << " - " << p[i + 1] + 1 << " : " << matr[p[i]][p[i + 1]] << endl;
			weight += matr[p[i]][p[i + 1]];
		}
		cout << "\n Загальна вага шляху: " << weight << endl << endl;
	}

	return 0;
}

int add_edges(int con_matr[N][N], int vert_degr[N], int matr[N][N]) {
	for (int i = 0; i < N; i++) {
		if (vert_degr[i] % 2 != 0) {
			for (int j = 0; j < N; j++) {
				if (vert_degr[j] % 2 != 0 && con_matr[i][j] != 0) {
					con_matr[i][j] = con_matr[i][j] + 1;
				}
			}
		}
	}

	cout << "\nЗмiнена матриця зв'язностi: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << con_matr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	euler(matr, con_matr);

	return 0;
}


int connectivity_matrix(int con_matr[N][N], int matr[N][N]) {
	cout << "\nМатриця зв'язностi: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matr[i][j] > 0) {
				con_matr[i][j] = 1;
			}
			else {
				con_matr[i][j] = matr[i][j];
			}
			cout << con_matr[i][j] << "\t";
		}
		cout << endl;
	}

	return **con_matr;
}


int if_euler(int con_matr[N][N], int vert_degr[N], int matr[N][N]) {
	for (int i = 0; i < N; i++) {
		if (vert_degr[i] != 0) {
			add_edges(con_matr, vert_degr, matr);
			break;
		}
		else {
			euler(matr, con_matr);
		}
	}

	return 0;
}

int vertex_degree(int con_matr[N][N], int vert_degr[N], int matr[N][N]) {
	cout << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			vert_degr[i] += con_matr[i][j];
		}
		if (vert_degr[i] % 2 != 0)
		{
			cout << "Вершина " << i + 1 << " - непарна \n";
		}
	}

	if_euler(con_matr, vert_degr, matr);

	return 0;
}


void main()
{
	setlocale(LC_ALL, "Ukrainian");
	int matr[N][N];
	int con_matr[N][N];
	int vert_degr[N];

	cout << "Кiлькiсть вершин: " << N << endl;
	cout << "Матриця ваг: " << endl;
	read_matrix(matr);
	connectivity_matrix(con_matr, matr);
	vertex_degree(con_matr, vert_degr, matr);

	system("pause");
}