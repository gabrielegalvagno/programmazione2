/*Le Strutture:

Definisci una struct Messaggio che contenga:

Un ID (intero).

Il testo del messaggio (stringa di max 100 caratteri).

Il tipo di log (es: "INFO", "WARN", "ERROR").

Il puntatore al nodo successivo.

Definisci la struct Coda.*/

#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"
#include <string.h>

int main(int argc, char *argv[])
{
    int error = 0;
    if (argc < 2)
    {
        fprintf(stderr, "insufficent arg \n");
        exit(1);
    }
    printf("LOG CHECK FILE %s\n", argv[1]);
    queue q;
    initqueue(&q);
    joinfilterqueue(&q, argv[1]);
    savetofile(&q, argv[2]);
    printf("Insert the error ID for lookup \n");
    scanf("%d", &error);
    findmessagebyid(&q, error);
    deletequeue(&q);
    emptycheck(&q);

    return 0;
}