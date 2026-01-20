#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funzioni.h"

int main(int argc, char *argv[])
{
    queue q;
    initqueue(&q);
    params p = decodeParameters(argc, argv);
    buildList(&q, argv[1]);
    printf("fatto\n");
    printqueue(&q);

    return 0;
}