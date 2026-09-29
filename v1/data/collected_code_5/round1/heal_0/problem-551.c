#include<stdlib.h>
#include<stdio.h>

#define ROW 5
#define COL 5

void extract_column(int arr[ROW][COL], int column, int *result) {
    for(int i = 0; i < ROW; i++) {
        result[i] = arr[i][column];
    }
}

int main(void) {
    //Initialize 2D matrix
    int arr[ROW][COL];
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            arr[i][j] = i + j; //Fill in dummy elements
        }
    }
    
    // Allocate enough space for the column
    int *column_elements = (int*) malloc(sizeof(int) * ROW);
    
    if(column_elements == NULL) {
       printf("Insufficient memory\n");
       return -1;
    }
    
    //Extract column 2
    int column_id = 2;
    if(column_id >= COL || column_id < 0) {
        printf("Column index out of bounds\n");
        free(column_elements);
        return -1;
    }
    
    extract_column(arr, column_id, column_elements);
    //Print elements in column 2
    for (int i=0; i<ROW; i++) {
        printf("%d ", column_elements[i]);
    }

    // Deallocate the column_elements array
    free(column_elements);
    return 0;
}