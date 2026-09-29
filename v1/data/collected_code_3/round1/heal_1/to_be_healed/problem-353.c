#include <stdio.h>
#include <stdlib.h>

void removeColumn(int **array, int rows, int cols, int colToRemove) {
    for (int i = 0; i < rows; i++) {
        for (int j = colToRemove; j < cols - 1; j++) {
            array[i][j] = array[i][j + 1];
        }
    }
}

int main() {
    int rows = 3, cols = 3;
    int **array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'array' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        array[i] = (int *)malloc(cols * sizeof(int));
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*array_47 + _10 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            array[i][j] = ++count;
        }
    }

    int colToRemove = 1;
    removeColumn(array, rows, cols, colToRemove);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}