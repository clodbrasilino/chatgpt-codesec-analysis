#include <stdio.h>
#include <stdlib.h>

int** removeColumn(int **arr, int rows, int cols, int colToRemove) {
    int i, j, k;
    int** new_arr = (int**) malloc(sizeof(int*) * rows);

    for(i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'new_arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        new_arr[i] = (int*) malloc(sizeof(int) * (cols - 1));

        if (new_arr[i] == NULL){ // Checking if memory was successfully allocated
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
        free(arr[i]); // de-allocating the memory of the old array
    }
    free(arr);
    return new_arr;
}

int main() {
    int rows = 3, cols = 3, colToRemove = 1;
    int i, j;
    int **arr = (int **) malloc(rows * sizeof(int *)); 
    for(i = 0; i<rows; i++) 
         /* Possible weaknesses found:
          *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
          */
         arr[i] = (int *) malloc(cols * sizeof(int)); 
  
    int count = 0;
    for(i = 0; i < rows; i++) 
        for(j = 0; j < cols; j++) 
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*arr_50 + _10 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            arr[i][j] = ++count;  // OR *(*(arr+i)+j) = ++count 
  
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