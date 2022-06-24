#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osobaStr {
	int nrRejstr;
	struct osobaStr* next;
};

void naPoczatek(struct osobaStr** head_ref, int new_data)
{
	struct osobaStr* replaceOne = (struct osobaStr*)malloc(sizeof(struct osobaStr));
	replaceOne->nrRejstr = new_data;
	replaceOne->next = (*head_ref);
	(*head_ref) = replaceOne;
}

void printPerson(const struct osobaStr* dane, const char* comment)
{
	if (dane == NULL)
	{
		printf("%s == NULL\n", comment);
	}
	else
	{
		printf("Rejstracja:%d \nAdres:%p \nNastepny w liscie:%p\n",
			dane->nrRejstr,
			dane,
			dane->next);
	}

}

void wydrukujListe(const struct osobaStr* list)
{
	printf("Drukuje liste:\n");
	const struct osobaStr* x;
	x = list;
	if (x == NULL)
	{
		printf("lista jest pusta\n");
	}
	else
	{
		while (x)
		{
			printPerson(x, "t");
			x = x->next;
		}
	}
}

void czyszczenie(struct osobaStr* list)
{
	struct osobaStr* next;
	while (list)
	{
		next = list->next;
		printf("Czyszcze %d\n", list->nrRejstr);
		free(list);
		list = next;
	}
}

int main()
{
	printf("Lista komend:\n x - zamknij program,\n wydrukuj - wydrukuj dane w liscie,\n [liczba] - dodaje rejstracje z podana liczba [NA POCZATEK LISTY]\n");

	struct osobaStr* one = NULL;
	struct osobaStr* nextOne = NULL;

	char komenda[64];
	int age;

	while (1)
	{
		printf("Wpisz polecenie: ");

		fgets(komenda, 64, stdin);
		if (strcmp("x\n", komenda) == 0)
		{
			printf("Zamykam program..\n");
			break;
		}

		else if (strcmp("wydrukuj\n", komenda) == 0)
		{
			printf("Drukuje..\n");
			wydrukujListe(one);
		}

		else if (sscanf(komenda, "%d", &age) != NULL)
		{
			printf("Dodaje %d\n", age);

			naPoczatek(&one, age);

		}
	}

	czyszczenie(one);
	one = NULL;
	nextOne = NULL;

	return 0;
}
