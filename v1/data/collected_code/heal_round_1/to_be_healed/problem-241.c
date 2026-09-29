#include <stdio.h>

void generate3DArray(char arr[][3][3], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
}

int main() {
    int size = 5; // Example size of the 3D array
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char arr[size][3][3];

    generate3DArray(arr, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i][j][k]' is initialized [premium-bughuntingUninit]
                 */
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}