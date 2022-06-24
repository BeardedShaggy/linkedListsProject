#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osobaStr {
	int nrRejstr;
	struct osobaStr* next;
};

struct osobaStr* dodajRejstracje(const int age)
{
	struct osobaStr* nowaOsoba = NULL;
	nowaOsoba = malloc(sizeof(struct osobaStr));
	if (nowaOsoba != NULL)
	{
		nowaOsoba->next = NULL;
		nowaOsoba->nrRejstr = age;
		printf("stworzono nowa rejstracje w pamieci: %p\n", nowaOsoba);
	}
	else
	{
		printf("Error: nie udalo sie dodac rejstracji \n");
	}
	return nowaOsoba;
}

void push(struct osobaStr** dodajRejstracje, int new_data)
{
	struct osobaStr* replaceOne = (struct osobaStr*)malloc(sizeof(struct osobaStr));
	replaceOne->nrRejstr = new_data;
	replaceOne->next = (*dodajRejstracje);
	(*dodajRejstracje) = replaceOne;
}

void printPerson(const struct osobaStr* person, const char* comment)
{
	if (person == NULL)
	{
		printf("%s == NULL\n", comment);
	}
	else
	{
		printf("%s: Rejstracja:%d address:%p nextInLine:%p\n",
			comment,
			person->nrRejstr,
			person,
			person->next);
	}

}

void wydrukujListe(const struct osobaStr* list)
{
	printf("Drukuje liste:\n");
	const struct osobaStr* t;
	t = list;
	if (t == NULL)
	{
		printf("lista jest pusta\n");
	}
	else
	{
		while (t)
		{
			printPerson(t, "t");
			t = t->next;
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
	printf("Lista komend:\n x - zamknij program,\n wydrukuj - wydrukuj dane w liscie,\n [liczba] - dodaje rejstracje z podana liczba\n");

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

		else if (strcmp("+poczatek\n", komenda) == 0)
		{
			sscanf(komenda, "%d", &age);
			printf("Podaj rejstracje zeby dodac ja na poczatek listy:\n");
			push(&one, age);
		}

		else if (sscanf(komenda, "%d", &age) != NULL)
		{
			printf("Dodaje %d\n", age);
			if (one == NULL)
			{
				one = dodajRejstracje(age);
				if (one != NULL)
				{
					nextOne = one;
				}
			}
			else
			{
				nextOne->next = dodajRejstracje(age);
				if (nextOne->next != NULL)
				{
					nextOne = nextOne->next;
				}
			}

		}
	}

	czyszczenie(one);
	one = NULL;
	nextOne = NULL;

	return 0;
}
