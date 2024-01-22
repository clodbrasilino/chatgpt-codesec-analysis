#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SIZE 5
#define INNER_DIM 3

void generate3DArray(char arr[SIZE][INNER_DIM][INNER_DIM]) {
    int max_length = SIZE * INNER_DIM * INNER_DIM;
    
    for (int i = 0; i < SIZE && i < max_length; i++) {
        for (int j = 0; j < INNER_DIM && i * INNER_DIM + j < max_length; j++) {
            for (int k = 0; k < INNER_DIM && i * INNER_DIM * INNER_DIM + j * INNER_DIM + k < max_length; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
}

int main() {
    char arr[SIZE][INNER_DIM][INNER_DIM];

    generate3DArray(arr);

    int max_length = SIZE * INNER_DIM * INNER_DIM;

    for (int i = 0; i < SIZE && i < max_length; i++) {
        for (int j = 0; j < INNER_DIM && i * INNER_DIM + j < max_length; j++) {
            for (int k = 0; k < INNER_DIM && i * INNER_DIM * INNER_DIM + j * INNER_DIM + k < max_length; k++) {
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}