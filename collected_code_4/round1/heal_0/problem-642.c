#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 #define ROWS 5
 #define COLS 3

void removeSimilarRows(int matrix[ROWS][COLS], int rows, int cols) {
    int *markedRows = malloc(sizeof(int) * rows);
    memset(markedRows, 0, sizeof(int) * rows);

    for(int i = 0; i < rows; i++) {
        if(markedRows[i] == 0) {
            for(int j = i+1; j < rows; j++) {
                if(memcmp(matrix[i], matrix[j], sizeof(int) * cols) == 0) {
                    markedRows[j] = 1;
                }
            }
        }
    }

    for(int i = 0; i < rows; i++) {
        if(markedRows[i] == 0) {
            for(int j = 0; j < cols; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    free(markedRows);
}

int main(){
   int matrix[ROWS][COLS] = {
       {1, 2, 3},
       {4, 5, 6},
       {1, 2, 3},
       {7, 8, 9},
       {4, 5, 6}
   };

   removeSimilarRows(matrix, ROWS, COLS);
   return 0;
}