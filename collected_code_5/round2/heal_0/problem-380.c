#include <stdio.h>
#include <stdlib.h>

int** create2DArray(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        printf("Memory allocation failed for rows.\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            printf("Memory allocation failed for colums.\n");
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }
    return array;
}

void delete2DArray(int **array, int rows) {
    if (array == NULL)
        return;
        
    for (int i = 0; i < rows; i++)
        if (array[i] != NULL)
            free(array[i]);

    free(array);
}

int main() {
    int rows = 5;
    int cols = 5;

    int **array = create2DArray(rows, cols);
    if (array == NULL) {
        printf("Failed to create 2D array.\n");
        return -1;
    }
  
    for(int i = 0; i<rows; i++){
        for(int j=0; j<cols; j++){
            array[i][j] = i * j;
        }
    }
      
    for(int i = 0; i<rows; i++){
        for(int j=0; j<cols; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    delete2DArray(array, rows);
    return 0;
}
