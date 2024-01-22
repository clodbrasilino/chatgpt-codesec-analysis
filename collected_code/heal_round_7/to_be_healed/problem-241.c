#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SIZE 5
#define INNER_DIM 3

/* Possible weaknesses found:
 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
 */
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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