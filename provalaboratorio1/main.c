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

    return 0;
}