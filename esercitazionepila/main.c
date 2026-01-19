#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include <string.h>

int main(int argc, char *argv[])
{
    pila p;
    initpila(&p);

    for (int i = 1; i < argc; i++)
    {
        push(&p, argv[i]);
    }
    printf("--- FIRST ELEMENT ---\n");
    printf("%s \n", peek(&p));

    printpila(&p);

    char ricerca[51];
    printf("Inserisci la parola di ricercare: ");
    scanf("%50s", ricerca);
    search(&p, ricerca);

    while (p.head != NULL)
    {
        pop(&p);
    }

    printpila(&p);

    return 0;
}