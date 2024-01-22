#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SIZE 5
#define INNER_DIM 3
#define MAX_LENGTH (SIZE*INNER_DIM*INNER_DIM)

/* Possible weaknesses found:
 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
 */
void generate3DArray(char arr[SIZE][INNER_DIM][INNER_DIM]) {
    
    if(MAX_LENGTH < SIZE * INNER_DIM * INNER_DIM) return;

    for (int i = 0; i < SIZE && i < MAX_LENGTH; i++) {
        for (int j = 0; j < INNER_DIM && j < MAX_LENGTH; j++) {
            for (int k = 0; k < INNER_DIM && k < MAX_LENGTH; k++) {
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

    if(MAX_LENGTH < SIZE * INNER_DIM * INNER_DIM) return 1;

    for (int i = 0; i < SIZE && i < MAX_LENGTH; i++) {
        for (int j = 0; j < INNER_DIM && j < MAX_LENGTH; j++) {
            for (int k = 0; k < INNER_DIM && k < MAX_LENGTH; k++) {
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}