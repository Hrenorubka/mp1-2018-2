#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <io.h>  
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct
{
	char name[200];
	long  calibre;
}FiLE;

// Капитан корабля под названием "21 группа"

void Pyzir(FiLE *a, int length)
{
	bool flag = true;
	FiLE obl;

	while (flag)
	{
		flag = false;
		for (int i = 2; i <= length + 1; i++)
			if (a[i - 2].calibre > a[i - 1].calibre)
			{
				obl = a[i - 2];
				a[i - 2] = a[i - 1];
				a[i - 1] = obl;
				flag = true;
			}
	}
}

// ALGORITM NA 3

void I_MUST_CHOOOSE(FiLE *a, int length)
{
	int n_min, n_max;
	FiLE obl;
	//int l = length;
	for (int i = 0; i < length; i++)
	{
		n_min = i;
		n_max = i;
		for (int k = i + 1; k <= length; k++)
		{
			if (a[k].calibre < a[n_min].calibre)
				n_min = k;
			if (a[k].calibre > a[n_max].calibre)
				n_max = k;
		}
		if (a[n_min].calibre != a[n_max].calibre)
		{
			obl = a[i];
			a[i] = a[n_min];
			a[n_min] = obl;
			obl = a[length];
			a[length] = a[n_max];
			a[n_max] = obl;
			length--;
		}
		else
			return;
	}
}

//ГУРРЕН-ЛАГАНН

void GURRREN_LAGANNNNNNNN(FiLE *a, FiLE *b, int beg, int end, int mid)
{
	int	k = beg;
	int i = 0, j = 0;
	while ((i <= mid - beg) && (j <= end - mid - 1))
		if (a[beg + i].calibre < a[mid + 1 + j].calibre)
		{
			b[i + j] = a[beg + i];
			i++;
		}
		else
		{
			b[i + j] = a[mid + 1 + j];
			j++;
		}
	if (i > mid - beg)
		for (int k = j; k <= end - mid - 1; k++)
			b[i + k] = a[mid + 1 + k];
	else
		for (int k = i; k <= mid - beg; k++)
			b[j + k] = a[beg + k];

	for (int k = beg; k <= end; k++)
		a[k] = b[k - beg];
}
void SIMOOOOON_SLIYANIE(FiLE *a, FiLE *b, int beg, int end)
{
	int mid;
	mid = (end + beg) / 2;
	if (end - beg == 0)
		return;
	SIMOOOOON_SLIYANIE(a, b, beg, mid);
	SIMOOOOON_SLIYANIE(a, b, mid + 1, end);
	GURRREN_LAGANNNNNNNN(a, b, beg, end, mid);
}

//Вставлять не сортировать!

int Something_Wrong(FiLE *a, int elem)
{
	int i = 0;
	while (a[i].calibre < a[elem].calibre)
		i++;
	return i;
}
void Vstav(FiLE *a, int length)
{
	int max_sponk = 0, i = 0;
	FiLE obl;
	bool flag = true;
	while ((i < length) && (flag == true))
	{
		if (a[i].calibre > a[i + 1].calibre)
			flag = false;
		else
		{
			max_sponk++;
			i++;
		}
	}
	for (int i = max_sponk + 1; i <= length; i++)
	{
		int res = Something_Wrong(a, i);
		obl = a[i];
		for (int j = i; j > res; j--)
			a[j] = a[j - 1];
		a[res] = obl;
	}
}

// Можно по быстрее, М?

void Qsort(FiLE *a, int down, int up)
{
	int i = down, j = up;
	FiLE obl;
	int mid = a[(up + down) / 2].calibre;
	do
	{
		while (a[i].calibre < mid)
			i++;
		while (a[j].calibre > mid)
			j--;
		if (i <= j)
		{
			obl = a[i];
			a[i] = a[j];
			a[j] = obl;
			i++;
			j--;
		}
	} while (i <= j);
	if (down < j)
		Qsort(a, down, j);
	if (up > i)
		Qsort(a, i, up);
}

// Здесь должна быть реклама очередной фермы...

void CreatePyramid(FiLE *a, int length)
{
	int vet = length / 2 - 1;
	FiLE obl;
	for (int i = vet; i >= 0; i--)
		if (a[i].calibre < a[2 * i + 1].calibre)
			if (a[i].calibre >= a[2 * i + 2].calibre)
			{
				obl = a[i];
				a[i] = a[2 * i + 1];
				a[2 * i + 1] = obl;
			}
			else if (a[2 * i + 2].calibre < a[2 * i + 1].calibre)
			{
				obl = a[i];
				a[i] = a[2 * i + 1];
				a[2 * i + 1] = obl;
			}
			else
			{
				obl = a[i];
				a[i] = a[2 * i + 2];
				a[2 * i + 2] = obl;
			}
		else if (a[i].calibre < a[2 * i + 2].calibre)
		{
			obl = a[i];
			a[i] = a[2 * i + 2];
			a[2 * i + 2] = obl;
		}
}
void Mavrodi(FiLE *a, int length)
{
	FiLE obl;
	CreatePyramid(a, length);
	for (int i = length; i > 0; i--)
	{
		obl = a[i];
		a[i] = a[0];
		a[0] = obl;
		CreatePyramid(a, i - 1);
	}
}

// ТЕЛО, Где мое Тело???

void main()
{
	int exit = 0;
	while (exit == 0)
	{
		setlocale(LC_ALL, "Rus");
		clock_t time;
		int choose;
		struct _finddata_t c_file;
		intptr_t hFile;
		char path[200];
		int count = 0;
		FiLE pam_pam[1000];
		FiLE b[1000];
		char string[200];
		int sh = 0;
		printf("Введите путь к фалам в формате c:\\temp\n");
		gets_s(string);
		strcat(string, "\\*.*");
		if ((hFile = _findfirst(string, &c_file)) == -1L)
			printf("В данной директории нет файлов =(\n");
		else
		{
			printf("Список файлов .c files\n\n");
			printf("ФАЙЛ%24c   РАЗМЕР\n", ' ');
			printf("----%24c   ----\n", ' ');
			do {
				char buffer[30];
				ctime_s(buffer, _countof(buffer), &c_file.time_write);
				if (count <= 200)
				{
					pam_pam[sh].calibre = c_file.size;
					strcpy(pam_pam[sh].name, c_file.name);
					printf("%-24.12s %10ld\n", c_file.name, c_file.size);
					sh++;
				}
				count++;
			} while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
		}
		printf("Выберете каким способом сориторовать:\n1) Пузырьком\n2) Встаками\n3) Слиянием\n4) Выбором\n5) Пирамидой\n6) Быстрой сортировкой\n");
		scanf_s("%d", &choose);
		printf("\n\n");
		time = clock();
		switch (choose)
		{
		case 1:
		{
			Pyzir(pam_pam, sh - 1);
			break;
		}
		case 2:
		{
			Vstav(pam_pam, sh - 1);
			break;
		}
		case 3:
		{
			SIMOOOOON_SLIYANIE(pam_pam, b, 0, sh - 1);
			break;
		}
		case 4:
		{
			I_MUST_CHOOOSE(pam_pam, sh - 1);
			break;
		}
		case 5:
		{
			Mavrodi(pam_pam, sh - 1);
			break;
		}
		case 6:
		{
			Qsort(pam_pam, 0, sh - 1);
			break;
		}
		}
		time = clock() - time;
		printf("Результат сортировки:\n\n");
		printf("ФАЙЛ%24c   РАЗМЕР\n", ' ');
		printf("----%24c   ----\n", ' ');
		for (int i = 0; i <= sh - 1; i++)
			printf("%-24.12s  %10ld\n", pam_pam[i].name, pam_pam[i].calibre);
		if ((int)time >= 1)
			printf("\nВремя программы: %d мс\nЕсли хотите еще посортировать введите 0\n", (int)time);
		else
			printf("\nВремя программы было меньше 1 мс\nЕсли хотите еще посортировать введите 0, если же нет, введите любую другую цифру\n");
		scanf_s("%d", &exit);
		if (exit == 0)
		{
			printf("Очистить консоль? 1) да 2) нет\n");
			scanf_s("%d", &choose);
			if (choose == 1)
				system("@cls||clear");
			gets_s(string);
		}
	}
}