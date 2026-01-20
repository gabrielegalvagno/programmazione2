#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*● B. Elaborazione Dati
Leggere tutti i record dal file binario e memorizzarli in una lista concatenata semplice. La lista deve essere mantenuta in ordine lessicografico crescente rispetto al campo codiceEvento.

● C. Visualizzazione
Stampare tutti i record della lista sullo standard output, dal primo all’ultimo.*/
#define MAXFILENAMELENGHT 20;

typedef struct
{
    char input_filename[20];
    char output_filename[20];
    int k;
} params;

typedef struct nodo
{
    char codiceEvento[31];
    char nomeLuogo[31];
    int capienzamax;
    struct nodo *next;
} nodo;

typedef struct
{
    nodo *head;
    nodo *tail;
    int dimensionequeue;
} queue;

void initqueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->dimensionequeue = 0;
}

// REVIEW - controllare la funzione
void insertRecord(queue *q, char codiceEvento[31], char nomeLuogo[31], int capienzamax)
{
    nodo *newnodo = malloc(sizeof(nodo));
    if (newnodo == NULL)
    {
        fprintf(stderr, "malloc not work \n");
        exit(1);
    }
}

void decodeParameters(int argc, char *argv[])
{
    params p;

    if (argc != 4)
    {
        fprintf(stderr, "insufficent params");
        exit(1);
    }

    if (strcmp(argv[3], "0") == 0)
    {
        p.k = 0;
    }
    else if (atoi(argv[3]) == 0)
    {
        fprintf(stderr, "k deve essere necessariamente un numero");
        exit(1);
    }
    else
    {
        p.k = atoi(argv[3]);
    }
    strcpy(p.input_filename, argv[1]);
    strcpy(p.output_filename, argv[2]);
    if (strcmp(&p.input_filename[strlen(p.input_filename) - 4], ".bin") || strcmp(&p.output_filename[strlen(p.output_filename) - 4], ".txt") != 0)
    {
        fprintf(stderr, "invalid file extensions");
        exit(1);
    }

    printf("Success params decode the number is %d\n", p.k);
}
