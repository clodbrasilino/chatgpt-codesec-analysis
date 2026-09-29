#include <stdio.h>
#include <stdlib.h>

#define MAX_N 99

static int **allocate_square(int n)
{
    int **square;
    int i;
    int j;

    square = malloc((size_t)n * sizeof(int *));
    if (square == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        square[i] = calloc((size_t)n, sizeof(int));
        if (square[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }

    return square;
}

static void free_square(int **square, int n)
{
    int i;

    if (square == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

static int generate_magic_square(int **square, int n)
{
    int row;
    int col;
    int value;
    int total;

    if (square == NULL || n < 1 || (n % 2) == 0) {
        return -1;
    }

    total = n * n;
    row = 0;
    col = n / 2;

    for (value = 1; value <= total; value++) {
        int new_row;
        int new_col;

        square[row][col] = value;

        new_row = (row - 1 + n) % n;
        new_col = (col + 1) % n;

        if (square[new_row][new_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = new_row;
            col = new_col;
        }
    }

    return 0;
}

static void print_square(int **square, int n)
{
    int i;
    int j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }
    printf("Magic constant: %d\n", n * (n * n + 1) / 2);
}

int main(void)
{
    int n;
    int **square;
    int result;

    printf("Enter odd square size (1-%d): ", MAX_N);

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 1 || n > MAX_N) {
        fprintf(stderr, "Error: size must be between 1 and %d\n", MAX_N);
        return EXIT_FAILURE;
    }

    if ((n % 2) == 0) {
        fprintf(stderr, "Error: size must be odd\n");
        return EXIT_FAILURE;
    }

    square = allocate_square(n);
    if (square == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = generate_magic_square(square, n);
    if (result != 0) {
        fprintf(stderr, "Error: failed to generate magic square\n");
        free_square(square, n);
        return EXIT_FAILURE;
    }

    print_square(square, n);
    free_square(square, n);

    return EXIT_SUCCESS;
}