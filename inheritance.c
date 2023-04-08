#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    srand(time(0));

    person *p = create_family(GENERATIONS);

    print_family(p, 0);

    free_family(p);
}

person *create_family(int generations)
{
    person *p = malloc(sizeof(person));

    if (generations > 1)
    {
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        p->parents[0] = parent0;
        p->parents[1] = parent1;
        p->alleles[0] = parent0->alleles[rand() % 2];
        p->alleles[1] = parent1->alleles[rand() % 2];
    }
    else
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    return p;
}

void print_family(person *p, int generation)
{
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    printf("%c%c\n", p->alleles[0], p->alleles[1]);

    if (p->parents[0] != NULL)
    {
        print_family(p->parents[0], generation + 1);
        print_family(p->parents[1], generation + 1);
    }
}

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);
}

char random_allele()
{
    char alleles[3] = {'A', 'B', 'O'};
    return alleles[rand() % 3];
}

