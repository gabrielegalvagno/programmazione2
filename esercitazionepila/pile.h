#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAPACITA 10

typedef struct node
{
    char string[51];
    struct node *next;

} node;

typedef struct
{
    struct node *head;
    int dimensione_attuale;
    int capacita_massima;
} pila;

void initpila(pila *p)
{
    p->head = NULL;
    p->dimensione_attuale = 0;
    p->capacita_massima = CAPACITA;
}

// REVIEW - completare logica if e return;
bool push(pila *p, const char *valore)
{

    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        fprintf(stderr, "malloc not work \n");
        exit(1);
    }

    strncpy(newNode->string, valore, 50);
    newNode->string[50] = '\0';

    newNode->next = p->head;
    p->head = newNode;
    p->dimensione_attuale++;

    return true;
}

bool pop(pila *p)
{

    if (p->head == NULL)
    {
        return false;
    }
    node *temp = p->head;
    p->head = p->head->next;
    p->dimensione_attuale--;
    if (p->dimensione_attuale == 0)
    {
        printf("the element removed is [%s], no element left\n", temp->string);
        free(temp);
        return true;
    }
    printf("the element removed is [%s], %d %s left\n",
           temp->string,
           p->dimensione_attuale,
           p->dimensione_attuale == 1 ? "element" : "elements");

    return true;
}

void printpila(pila *p)
{
    if (p == NULL || p->head == NULL)
    {
        printf("empty stack.\n");
        exit(1);
    }
    node *temp = p->head;
    printf("--- stack content to the top ---\n");
    while (temp != NULL)
    {
        printf("[%s] ", temp->string);
        temp = temp->next;
    }
    printf("\n------------------------------------------\n");
}

char *peek(pila *p)
{
    if (p->head == NULL)
    {
        return NULL;
    }
    return p->head->string;
}
void search(const pila *p, const char *valore)
{
    node *curr = p->head;
    int posizione = 1;
    bool trovato = false;
    while (curr != NULL)
    {
        if (strcmp(curr->string, valore) == 0)
        {
            printf("\n Corrispondenza trovata! alla posizione numero: %d \n", posizione);
            trovato = true;
        }
        curr = curr->next;
        posizione++;
    }
    if (!trovato)
    {
        printf("\nNessuna corrispondenza per: %s\n", valore);
        printf("\n------------------------------------------\n");
    }
}
