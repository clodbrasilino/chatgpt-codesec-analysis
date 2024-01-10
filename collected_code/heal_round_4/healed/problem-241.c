#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SIZE 5
#define INNER_DIM 3
#define MAX_LENGTH (SIZE*INNER_DIM*INNER_DIM)

void generate3DArray(char arr[SIZE][INNER_DIM][INNER_DIM]) {

    assert(MAX_LENGTH >= SIZE * INNER_DIM * INNER_DIM);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < INNER_DIM; j++) {
            for (int k = 0; k < INNER_DIM; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
}

int main() {

    char arr[SIZE][INNER_DIM][INNER_DIM];

    generate3DArray(arr);

    assert(MAX_LENGTH >= SIZE * INNER_DIM * INNER_DIM);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < INNER_DIM; j++) {
            for (int k = 0; k < INNER_DIM; k++) {
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}