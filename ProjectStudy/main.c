#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osobaStr {
	int nrRejstr;
	struct osobaStr* next;
};

void dodajPoczatek(struct osobaStr** one, int new_data) //Dodaje na poczatek listy wiazanej
{
	struct osobaStr* replaceOne = (struct osobaStr*)malloc(sizeof(struct osobaStr));
	replaceOne->nrRejstr = new_data;
	replaceOne->next = (*one);
	(*one) = replaceOne;
}

void dodajKoniec(struct osobaStr** one, int new_data) //dodaje nowa rejstracje na koniec listy wiazanej
{
	struct osobaStr* new_node = (struct osobaStr*)malloc(sizeof(struct osobaStr));
	struct osobaStr* last = *one;

	new_node->nrRejstr = new_data;
	new_node->next = NULL;

	if (*one == NULL)
	{
		*one = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return;
}

void printujOsobe(const struct osobaStr* dane, const char* comment) //Printuje dane
{
	if (dane == NULL)
	{
		printf("%s == NULL\n", comment);
	}
	else
	{
		printf("\n \nRejstracja:%d \nAdres:%p \nNastepny w liscie:%p\n\n",
			dane->nrRejstr,
			dane,
			dane->next
		);
	}

}

void wydrukujListe(const struct osobaStr* list) //Drukuje liste
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
			printujOsobe(x, "t");
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

	char komenda[64]; //przechowuje komende numer 1 (main menu)
	char komenda2[64]; //przechowuje komende numer 2 (menu dodawania)
	int number;

	while (1)
	{
		printf("Wpisz polecenie: \n");

		fgets(komenda, 64, stdin);
		if (strcmp("x\n", komenda) == 0)
		{
			printf("Zamykam program..\n");
			break;
		}

		else if (strcmp("wydrukuj\n", komenda) == 0)
		{
			printf("\n");
			wydrukujListe(one);
		}

		else if (sscanf(komenda, "%d", &number) != NULL)
		{
			printf("Wybierz gdzie dodac rejstracje: %d\n Do wyboru:\n poczatek\n koniec\n", number);
			fgets(komenda2, 64, stdin);

			if (strcmp("poczatek\n", komenda2) == 0) {
				dodajPoczatek(&one, number);
				printf("\n dodano rejstracje na poczatek \n");
			}
			else if (strcmp("koniec\n", komenda2) == 0) {
				dodajKoniec(&one, number);
				printf("\n dodano rejstracje na koniec \n");
			}

		}
	}

	czyszczenie(one);
	one = NULL;
	nextOne = NULL;

	return 0;
	//Stworzone przez Marcin Cudny dla WSB
}
