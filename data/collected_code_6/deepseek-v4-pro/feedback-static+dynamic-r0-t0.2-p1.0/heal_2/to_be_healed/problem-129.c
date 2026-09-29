#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int **generate_magic_square(int n) {
    if (n % 2 == 0) {
        return NULL;
    }

    if (n <= 0 || n > INT_MAX / (int)sizeof(int *)) {
        return NULL;
    }

    int **square = (int **)malloc((size_t)n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Variable 'allocation_failed' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'allocation_failed' can be reduced. [variableScope]
     */
    int allocation_failed = 0;
    for (int i = 0; i < n; i++) {
        square[i] = (int *)calloc((size_t)n, sizeof(int));
        if (square[i] == NULL) {
            /* Possible weaknesses found:
             *  Value stored to 'allocation_failed' is never read [deadcode.DeadStores]
             *  Variable 'allocation_failed' is assigned a value that is never used. [unreadVariable]
             */
            allocation_failed = 1;
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
    if (square == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

void print_magic_square(int **square, int n) {
    if (square == NULL) {
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

int main(void) {
    int n;
    printf("Enter odd number for magic square size: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n <= 0 || n % 2 == 0) {
        printf("Please enter a positive odd number\n");
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