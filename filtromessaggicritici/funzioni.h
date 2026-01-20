/*Le Funzioni da implementare:

void enqueue(...): Inserisce un nuovo messaggio.

Messaggio dequeue(...): Rimuove un messaggio e lo restituisce.

void filterQueue(...): Questa è la parte centrale. Scorri la coda e:

Se il messaggio è di tipo "ERROR", trasformalo tutto in MAIUSCOLO.

Se il messaggio è più lungo di 50 caratteri, troncalo a 47 e aggiungi "..." alla fine.

void saveToFile(...): Scrive il contenuto finale della coda su un file chiamato report.txt.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct msg
{
    int id;
    char body[100];
    char logtype[10];
    struct msg *next;
} msg;

typedef struct queue
{
    msg *head;
    msg *tail;
    int count;
} queue;

void initqueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
}

void enqueue(queue *q, int id, char *type, char *testo)
{
    msg *newmsg = (msg *)malloc(sizeof(msg));
    if (newmsg == NULL)
    {
        fprintf(stderr, "malloc not worked \n");
        exit(1);
    }
    newmsg->id = id;
    strncpy(newmsg->body, testo, 99);
    newmsg->body[99] = '\0';
    strncpy(newmsg->logtype, type, 9);
    newmsg->logtype[9] = '\0';
    newmsg->next = NULL;

    if (q->head == NULL)
    {
        q->head = newmsg;
        q->tail = newmsg;
    }
    else
    {
        q->tail->next = newmsg;
        q->tail = newmsg;
    }

    q->count++;
}

void dequeue(queue *q, int *id, char *type, char *text)
{
    if (q->head == NULL)
    {
        fprintf(stderr, "the queue is empty \n");
        exit(1);
    }

    msg *temp = q->head;

    *id = temp->id;
    strcpy(type, temp->logtype);
    strcpy(text, temp->body);

    q->head = q->head->next;

    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(temp);

    q->count--;
}

void joinfilterqueue(queue *q, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "errore nell'apertura del file \n");
        exit(10);
    }
    int id;
    char type[10];
    char message[100];

    while (fscanf(fp, "%d %s %99s", &id, type, message) != EOF)
    {
        if (strcmp(type, "ERROR") == 0)
        {
            for (int i = 0; message[i] != '\0'; i++)
            {
                message[i] = toupper(message[i]);
            }
        }

        int len = strlen(message);
        if (len > 50)
        {
            message[46] = '.';
            message[47] = '.';
            message[48] = '.';
            message[49] = '\0';
        }
        enqueue(q, id, type, message);
    }
}

void printqueue(queue *q)
{

    msg *temp = q->head;
    if (temp == NULL)
    {
        fprintf(stderr, "the queue is empty \n");
        exit(1);
    }

    while (temp != NULL)
    {
        printf("%d %s %s \n", temp->id, temp->logtype, temp->body);
        temp = temp->next;
    }
}

void savetofile(queue *q, char *filename)
{
    FILE *fp = fopen(filename, "w");
    msg *temp = q->head;

    if (fp == NULL)
    {
        fprintf(stderr, "file opening error");
        exit(1);
    }

    fprintf(fp, "--- SYSTEM LOG ---\n");

    while (temp != NULL)
    {
        fprintf(fp, "[ID: %d] [%s] message: %s \n", temp->id, temp->logtype, temp->body);
        temp = temp->next;
    }
    fclose(fp);

    printf("FILE [%s] SAVING SUCCESS\n", filename);
}

void findmessagebyid(queue *q, int searchid)
{
    msg *temp = q->head;
    bool trovato = false;
    if (temp == NULL)
    {
        fprintf(stderr, "the queue is empty");
    }
    printf("\n ============== FINDING MESSAGE ID: %d ============== \n", searchid);

    while (temp != NULL)
    {

        if (temp->id == searchid)
        {
            printf("FINDED! \n");
            printf("TYPE: [%s]\n", temp->logtype);
            printf("MSG: %s\n", temp->body);
            printf("==================================================== \n", searchid);
            trovato = true;
            break;
        }
        temp = temp->next;
    }
    if (!trovato)
    {
        printf("NO ID FOUNDED \n");
    }
}

void deletequeue(queue *q)
{
    msg *temp = q->head;
    while (temp != NULL)
    {
        msg *next = temp->next;
        free(temp);
        temp = next;
    }
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;

    printf("queue delete success\n");
}

void emptycheck(queue *q)
{
    if (q->head == NULL)
    {
        printf("the queue is empty \n");
    }
    else
    {
        printf("the queue is full \n");
    }
}
