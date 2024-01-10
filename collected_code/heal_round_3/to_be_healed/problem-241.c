#include <stdio.h>

#define SIZE 5
#define INNER_DIM 3
#define MAX_LENGTH (SIZE*INNER_DIM*INNER_DIM)

/* Possible weaknesses found:
 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
 */
void generate3DArray(char arr[SIZE][INNER_DIM][INNER_DIM]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < INNER_DIM; j++) {
            for (int k = 0; k < INNER_DIM; k++) {
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