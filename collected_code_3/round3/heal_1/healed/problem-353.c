#include <stdio.h>
#include <stdlib.h>

void removeColumn(int** arr, int rows, int cols, int colToRemove) {
    int i, j;
    for(i = 0; i < rows; i++) {
        for(j = colToRemove; j < cols - 1; j++) {
            arr[i][j] = arr[i][j+1];
        }
        int* temp = realloc(arr[i], (cols - 1) * sizeof(int));
        if (temp == NULL) {
            free(arr[i]);
            exit(1);
        } else {
            arr[i] = temp;
        }
    }
}

int main() {
    int rows = 3, cols = 4, colToRemove = 2;
    int** arr = malloc(rows * sizeof(int*));
    if (arr == NULL) {
        exit(1);
    }

    int i, j;
    for(i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(int));
        if(arr[i] == NULL) {
            for(j=0; j<i; j++)
                free(arr[j]);
            free(arr);
            exit(1);
        }
        for(j = 0; j < cols; j++) {
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