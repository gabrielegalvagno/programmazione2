#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGHT 50

__attribute__((noreturn)) void terminateProgram()
{
    exit(1);
}

typedef struct
{
    char input_filename[101];
    char output_filename[101];
} file;

typedef struct nodo
{
    char stringa[51];
    struct nodo *next;
} Nodo;

typedef struct
{
    Nodo *head;
    Nodo *tail;
} queue;

file decodeParameters(int argc, char *argv[])
{
    file f;
    if (argc < 3)
    {
        fprintf(stderr, "insufficient parameters\n");
        terminateProgram();
    }

    strncpy(f.input_filename, argv[1], 100);
    f.input_filename[100] = '\0';
    strncpy(f.output_filename, argv[2], 100);
    f.output_filename[100] = '\0';

    if (strlen(f.input_filename) < 4 || strcmp(&f.input_filename[strlen(f.input_filename) - 4], ".txt") != 0)
    {
        fprintf(stderr, "the file must be a .txt\n");
        terminateProgram();
    }
    if (strlen(f.output_filename) < 4 || strcmp(&f.output_filename[strlen(f.output_filename) - 4], ".txt") != 0)
    {
        fprintf(stderr, "the file must be a .txt\n");
        terminateProgram();
    }
    return f;
}

void initqueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(queue *q, char *valore)
{
    Nodo *newNode = (Nodo *)malloc(sizeof(Nodo));
    if (!newNode)
        exit(1);
    strncpy(newNode->stringa, valore, 50);
    newNode->stringa[50] = '\0';
    newNode->next = NULL;

    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void filetoqueue(char *input_filename, queue *q)
{
    FILE *fp = fopen(input_filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "error opening file\n");
        exit(1);
    }

    char buffer[51];
    while (fscanf(fp, "%50s", buffer) != EOF)
    {
        enqueue(q, buffer);
    }
    fclose(fp);
}

char *dequeue(queue *q, char *buffer)
{
    if (q->head == NULL)
    {
        fprintf(stderr, "the queue is empty \n");
        exit(1);
    }

    Nodo *temp = q->head;

    strcpy(buffer, temp->stringa);
    buffer[50] = '\0';

    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(temp);

    return buffer;
}

void invertiStringa(char *s)
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
}

void processQueue(queue *q)
{

    int n = 0;
    Nodo *corr = q->head;
    while (corr != NULL)
    {
        n++;
        corr = corr->next;
    }

    char buffer[51];

    for (int i = 0; i < n; i++)
    {
        dequeue(q, buffer); // Estraiamo la stringa [cite: 15]

        int len = strlen(buffer);

        if (len % 2 != 0)
        {
            // Se dispari, invertiamo [cite: 17]
            invertiStringa(buffer);
        }
        // Se è pari, non facciamo nulla al buffer [cite: 16]

        // 3. Reinseriamo in ogni caso per mantenere l'ordine FIFO [cite: 18]
        enqueue(q, buffer);
    }
}

void printqueue(queue *q)
{

    Nodo *curr = q->head;

    if (curr == NULL)
    {
        fprintf(stderr, "empty queue.\n");
        exit(1);
    }
    char buffer[50];
    while (curr != NULL)
    {
        printf("%s \n", curr->stringa);
        curr = curr->next;
    }
}