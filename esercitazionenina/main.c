#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funzioni.h"

int main(int argc, char *argv[])
{
    file parametri = decodeParameters(argc, argv);

    printf("======= STAMPA PARAMETRI =======\n");
    printf("nome file di input: %s\n", parametri.input_filename);
    printf("nome file di output: %s\n", parametri.output_filename);

    queue q;

    initqueue(&q);

    filetoqueue(parametri.input_filename, &q);
    printf("======= CONTENUTO DELLA CODA INIZIALE =======\n");
    printqueue(&q);

    processQueue(&q);
    printf("======= CONTENUTO DELLA CODA FINALE =======\n");
    printqueue(&q);

        return 0;
}