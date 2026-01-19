// NOTE - //FATTO controllare se gli argomenti sono 3, // FATTO controllare se gli argomenti finisco con .txt, //FATTO controllare che abbiamo lunghezza massima di 100 char

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGHT 100;

typedef struct
{
    char input_filename[100];
    char output_filename[100];
} file;

typedef struct
{
    char stringa[50];
    struct nodo *next;
} nodo;

typedef struct
{
    nodo *head;
    nodo *tail;
} queue;

void initqueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(queue *q, char *valore)
{
    nodo *newnodo = (nodo *)malloc(sizeof(nodo));

    strncpy(newnodo->stringa, valore, 50);
    newnodo->stringa[50] = '\0';
    newnodo->next = NULL;

    if (q->head == NULL)
    {
        q->head = newnodo;
        q->tail = newnodo;
    }
    else
    {
        q->tail->next = newnodo;
        q->tail = newnodo;
    }
}

file decodeParameters(int argc, char *argv[])
{
    file f;

    if (argc < 3)
    {
        fprintf(stderr, "insufficient paremeters \n");
        exit(1);
    }

    strncpy(f.input_filename, argv[1], 100);
    f.input_filename[100] = '\0';

    strncpy(f.output_filename, argv[2], 100);
    f.output_filename[100] = '\0';

    if (strcmp(&f.input_filename[strlen(f.input_filename) - 4], ".txt") != 0)
    {
        fprintf(stderr, "the file must be a .txt \n");
        exit(1);
    }

    if (strcmp(&f.output_filename[strlen(f.output_filename) - 4], ".txt") != 0)
    {
        fprintf(stderr, "the file must be a .txt \n");
        exit(1);
    }

    return f;
}
