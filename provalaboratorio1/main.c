#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char *argv[])
{

    file params = decodeParameters(argc, argv);

    printf("======A Stampa Parametri======\n");
    printf("input_filename: %s\n", params.input_filename);
    printf("output_filename: %s\n", params.output_filename);

    queue q;

    initqueue(&q);

    filetoqueue(params.input_filename, &q);
    printf("======B Contenuto della Coda Q (iniziale) ======\n");
    printqueue(&q);

    processQueue(&q);
    printf("======B Contenuto della Coda Q (finale) ======\n");
    printqueue(&q);

    char R[100][51];
    char buffer[51];
    int ac = 0;
    while (q.head != NULL)
    {
        dequeue(&q, buffer);
        strcpy(R[ac], buffer);
        ac++;
    }
    for (int i = 0; i < ac - 1; i++)
    {
        for (int j = 0; j < ac - i - 1; j++)
        {

            if (strcmp(R[j], R[j + 1]) > 0)
            {

                char temp[51];
                strcpy(temp, R[j]);
                strcpy(R[j], R[j + 1]);
                strcpy(R[j + 1], temp);
            }
        }
    }
    printf("======ARRAY ORDINATO PER NOME ======\n");
    int i = 0;
    while (i < ac)
    {
        printf("%s \n", R[i]);
        i++;
    }

    return 0;
}