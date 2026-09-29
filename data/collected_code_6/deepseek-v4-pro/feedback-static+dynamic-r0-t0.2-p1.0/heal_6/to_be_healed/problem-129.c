#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int **generate_magic_square(int n) {
    if (n <= 0 || n % 2 == 0) {
        return NULL;
    }

    if (n > INT_MAX / (int)sizeof(int)) {
        return NULL;
    }

    if ((size_t)n > SIZE_MAX / sizeof(int *)) {
        return NULL;
    }

    int **square = (int **)malloc((size_t)n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        square[i] = (int *)calloc((size_t)n, sizeof(int));
        if (square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }

    int row = 0;
    int col = n / 2;

    for (int num = 1; num <= n * n; num++) {
        square[row][col] = num;
        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (square[next_row][next_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    return square;
}

void free_magic_square(int **square, int n) {
    if (square == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(square[i]);
        square[i] = NULL;
    }
    free(square);
}

void print_magic_square(int **square, int n) {
    if (square == NULL || n <= 0) {
        printf("Invalid magic square\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (square[i] == NULL) {
            printf("Invalid magic square\n");
            return;
        }
        for (int j = 0; j < n; j++) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:17766,execs:3636,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int n = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];

    printf("Enter odd number for magic square size: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    char *endptr = NULL;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        printf("Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'val<=0' is not redundant
     */
    if (val <= 0 || val > INT_MAX) {
        printf("Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Assignment 'n=(int)val', assigned value is greater than 0
     */
    n = (int)val;

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     */
    if (n <= 0 || n % 2 == 0) {
        printf("Please enter a positive odd number\n");
        return 1;
    }

    if (n > INT_MAX / (int)sizeof(int)) {
        printf("Size too large\n");
        return 1;
    }

    int **magic_square = generate_magic_square(n);
    if (magic_square == NULL) {
        printf("Failed to generate magic square\n");
        return 1;
    }

    print_magic_square(magic_square, n);
    free_magic_square(magic_square, n);

    return 0;
}