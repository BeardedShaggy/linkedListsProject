#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osobaStr {
    int nrRejstr;
    struct osobaStr* nextInLine;
    char imieWlasciciela[64];
};

struct osobaStr* dodajRejstracje(const int age)
{
    struct osobaStr* nowaOsoba = NULL;
    nowaOsoba = malloc(sizeof(struct osobaStr));
    if (nowaOsoba != NULL)
    {
        nowaOsoba->nextInLine = NULL;
        nowaOsoba->nrRejstr = age;
        printf("stworzono nowa rejstracje w pamieci: %p\n", nowaOsoba);
    }
    else
    {
        printf("Error: nie udalo sie dodac rejstracji \n");
    }
    return nowaOsoba;
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
            person->nextInLine);
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
            t = t->nextInLine;
        }
    }
}

void czyszczenie(struct osobaStr* list)
{
    struct osobaStr* next;
    while (list)
    {
        next = list->nextInLine;
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
        printf("Enter a command or value : ");
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
                nextOne->nextInLine = dodajRejstracje(age);
                if (nextOne->nextInLine != NULL)
                {
                    nextOne = nextOne->nextInLine;
                }
            }

        }
    }

    czyszczenie(one);
    one = NULL;
    nextOne = NULL;

    return 0;
}

