// NOTE - //FATTO controllare se gli argomenti sono 3, // FATTO controllare se gli argomenti finisco con .txt, //FATTO controllare che abbiamo lunghezza massima di 100 char

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILENAME_LENGHT 100; // DEFINISCE LA MASSIMA LUNGHEZZA DI CARATTERI DEL FILE

typedef struct // STRUTTURA DI TIPO FILE DOVE SONO CONTENUTI 2 ARRAY DI CARATTERI CHE SERVIRANNO A DARE I NOMI AI FILE I/O
{
    char input_filename[100];
    char output_filename[100];
} file;

typedef struct nodo // STRUTTURA CHE DEFINISCE UN NODO CHE CONTIENE UN ARRAY DI CARATTERI, E UN PUNTATORE NEXT AD UN NUOVO NODO
{
    char stringa[50];
    struct nodo *next;
} nodo;

typedef struct // STRUTTURA CHE DEFINISCE LA CODA CHE CONTIENE DUE PUNTATORI DI TIPO NODO, ALLA TESTA E ALLA CODA DELLA QUEUE
{
    nodo *head;
    nodo *tail;
    int dimensionecoda;
} queue;

void initqueue(queue *q) // FUNZIONE CHE INIZIALIZZA LA CODA
{
    q->head = NULL;
    q->tail = NULL;
    q->dimensionecoda = 0;
}

void enqueue(queue *q, char *valore)
{
    nodo *newnodo = (nodo *)malloc(sizeof(nodo));

    strncpy(newnodo->stringa, valore, 50); // MEMORIZZA IL VALORE INSERITO DALL'UTENTE NEL NUOVONODO
    newnodo->stringa[50] = '\0';           // ELIMINA L'ULTIMO CARATTERE
    newnodo->next = NULL;                  // CREA IL PROSSIMO NODO

    // NOTE - STRUTTURA DI CONTROLLO PER L'INSERIMENTO DEI NUOVI
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

    q->dimensionecoda++;
}

file decodeParameters(int argc, char *argv[]) // FUNZIONE CHE MEMMORIZZA GLI ARGOMENTI NELLA STRUTTURA FILE, E CONTROLLA CHE IL NUMERO DI ARG SIA SUFF., E CHE L'ESTENSIONE SIA .TXT
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

char *dequeue(queue *q, char *valore)
{
    if (q->head == NULL)
    {
        fprintf(stderr, "the queue is empty \n");
        exit(1);
    }

    nodo *temp = q->head;
    strcpy(valore, temp->stringa);
    valore[50] = '\0';

    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    free(temp);

    q->dimensionecoda--;

    return valore;
}
char *invertistringa(char *s)
{
    int inizio = 0;
    int fine = strlen(s) - 1;
    while (inizio < fine)
    {
        char temp = s[inizio];
        s[inizio] = s[fine];
        s[fine] = temp;
        inizio++;
        fine--;
    }
    return s;
}

void processQueue(queue *q)
{
    nodo *temp = q->head;

    char buffer[50];
    int n = q->dimensionecoda;

    for (int i = 0; i < n; i++)
    {
        dequeue(q, buffer);

        int len = strlen(buffer);

        if (len % 2 != 0)
        {
            invertistringa(buffer);
        }

        enqueue(q, buffer);
    }
}

void printqueue(queue *q)
{
    nodo *temp = q->head;
    if (temp == NULL)
    {
        fprintf(stderr, "the queue is empty \n");
        exit(1);
    }

    char buffer[50];
    while (temp != NULL)
    {
        printf("%s \n", temp->stringa);
        temp = temp->next;
    }
}

void filetoqueue(char *input_filename, queue *q)
{
    FILE *fp = fopen(input_filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "error opening file \n");
        exit(1);
    }

    char buffer[50];
    while (fscanf(fp, "%50s", buffer) != EOF)
    {
        enqueue(q, buffer);
    }
    fclose(fp);
}
