#include <stdio.h>
#include <stdlib.h>

int** generate2DArray(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    for(int i=0; i<rows; i++)
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'array' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        array[i] = (int *)malloc(cols * sizeof(int));

    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*array_26 + _10 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            array[i][j] = i + j;

    return array;
}

int main() {
    int rows = 5, cols = 5;
    int **array = generate2DArray(rows, cols);

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<rows; i++)
        free(array[i]);
    free(array);

    return 0;
}