#include <stdio.h>
#include <stdlib.h>

int** removeColumn(int **arr, int rows, int cols, int colToRemove) {
    int i, j, k;
    int** new_arr = (int**) malloc(sizeof(int*) * rows);

    if(new_arr == NULL)
        return NULL;

    for(i = 0; i < rows; i++) {
        new_arr[i] = (int*) malloc(sizeof(int) * (cols - 1));

        if (new_arr[i] == NULL){ 
            for(j = 0; j < i; j++) {
                free(new_arr[j]);
            }
            free(new_arr);
            return NULL;
        }
    }

    for(i = 0; i < rows; i++) {
        for(j = 0, k = 0; j < cols; j++) {
            if(j != colToRemove) {
                new_arr[i][k] = arr[i][j];
                k++;
            }
        }
    }

    for(i = 0; i < rows; i++) {
        free(arr[i]); 
    }
    free(arr);

    return new_arr;
}

int main() {
    int rows = 3, cols = 3, colToRemove = 1;
    int i, j;
    int **arr = (int **) malloc(rows * sizeof(int *)); 

    if(arr == NULL)
        return 0;

    for(i = 0; i<rows; i++) {
        arr[i] = (int *) malloc(cols * sizeof(int)); 

        if(arr[i] == NULL){
            for(j = 0; j < i; j++){
                free(arr[j]);
            }
            free(arr);
            return 0;
        }
    }

    int count = 0;
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            arr[i][j] = ++count;

    arr = removeColumn(arr, rows, cols, colToRemove);
    if(arr == NULL) {
        printf("Error! memory not allocated.");
        return 0;
    }

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols - 1; j++){
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