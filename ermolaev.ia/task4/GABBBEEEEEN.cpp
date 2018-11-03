#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>


void main()
{
	struct Melochi_jizni
	{
		//int kod1, kod2, kod3, kod4;
		int kod[4];
		char name[25];
		int cost_one;
		int cost_all, cost_all_nodiscount;
		int kol;
		int discount;
	};
	setlocale(LC_ALL, "Rus");
	FILE *file;
	errno_t err;
	err = fopen_s(&file, "klap_klap.txt", "r");
	Melochi_jizni food[1000];
	int i = 0;
	for (i = 0; i < 24; i++)
	{
		//fscanf_s(file, "%d%d%d%d", &food[i].kod1, &food[i].kod2, &food[i].kod3, &food[i].kod4);
		for (int j = 0; j < 4; j++)
			fscanf_s(file, "%d", &food[i].kod[j]);
		fscanf_s(file, "%s%d%d", &food[i].name, sizeof(food[i].name), &food[i].cost_one, &food[i].discount);
		food[i].cost_all = 0;
		food[i].kol = 0;
		food[i].cost_all_nodiscount = 0;
	}
	printf("Таблица штрих-кодов \n");
	for (i = 0; i < 24; i++)
	{
		//printf("%d %d %d %d ", food[i].kod1, food[i].kod2, food[i].kod3, food[i].kod4);
		for (int j = 0; j < 4; j++)
			printf("%d ", food[i].kod[j]);
		printf("%s %d %d \n", food[i].name, food[i].cost_one, food[i].discount);
	}

	int kol_prod = 0;
	int shtrix[4];
	int sum = 0;
	int buy = 11;
	int choose = 1;

	while (choose == 1)
	{
		printf("Введите Штрих-код продукта: \n");
		for (i = 0; i < 4; i++)
		{
			scanf_s("%d", &shtrix[i]);
		}
		i = 0;
		while ((i < 24) && ((shtrix[0] != food[i].kod[0]) || (shtrix[1] != food[i].kod[1]) || (shtrix[2] != food[i].kod[2]) || (shtrix[3] != food[i].kod[3])))
			i++;
		if (i < 24)
		{
			food[i].kol++;
			if (food[i].kol == 1)
				kol_prod++;
			food[i].cost_all_nodiscount = food[i].cost_one + food[i].cost_all_nodiscount;
			if (food[i].kol < 3)
			{
				food[i].cost_all = food[i].cost_one + food[i].cost_all;
				sum = food[i].cost_one + sum;
			}
			else
			{
				food[i].cost_all = food[i].cost_one*(1 - 0.01 * food[i].discount) + food[i].cost_all;
				sum = sum + food[i].cost_one*(1 - 0.01 * food[i].discount);
			}
			printf("Информация о вашем товаре: \n");
			printf("Имя товара: %s\nЕго стоимость: %d рублей \n\n", food[i].name, food[i].cost_one);

		}
		else
		{
			printf("Такого товара в базе нет =( \n");
		}
		printf("Сформировать чек? 0. да 1. нет\n");
		scanf_s("%d", &choose);
	}
	i = 0;
	printf("Ваш чек:\n");
	printf("Название товара:	Колличество:	Стоимость:		Скидка(в руб):\n");
	while ((i < 24) && (kol_prod != 0))
	{
		if (food[i].kol > 0)
		{
			printf("%s			%d		%d			%d\n", food[i].name, food[i].kol, food[i].cost_all, food[i].cost_all_nodiscount - food[i].cost_all);
			kol_prod--;
		}
		i++;
	}
	printf("ИТОГО: %d рублей", sum);
	while (true);


}