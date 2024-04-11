#include <stdio.h>
#include <stdlib.h>

void removeColumn(int** arr, int rows, int cols, int colToRemove) {
    int i, j, k;
    for(i = 0; i < rows; i++) {
        for(j = colToRemove; j < cols - 1; j++) {
            arr[i][j] = arr[i][j+1];
        }
        arr[i] = realloc(arr[i], (cols - 1) * sizeof(int));
    }
}

int main() {
    int rows = 3, cols = 4, colToRemove = 2;
    int** arr = malloc(rows * sizeof(int*));
    int i, j;

    for(i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = malloc(cols * sizeof(int));
        for(j = 0; j < cols; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*arr_46 + _11 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            arr[i][j] = i * cols + j;
        }
    }

    removeColumn(arr, rows, cols, colToRemove);

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols - 1; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}