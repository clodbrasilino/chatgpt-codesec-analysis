#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int **generate_magic_square(int n);
void free_magic_square(int **square, int n);
void print_magic_square(int **square, int n);

int **generate_magic_square(int n)
{
    int **square;
    int row;
    int col;
    int next_row;
    int next_col;
    int num;
    int i;
    int j;
    int total;

    if (n < 1 || n % 2 == 0 || (long long)n * n > INT_MAX)
    {
        return NULL;
    }

    square = malloc((size_t)n * sizeof(*square));
    if (square == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        square[i] = calloc((size_t)n, sizeof(*square[i]));
        if (square[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }

    row = 0;
    col = n / 2;
    total = n * n;

    for (num = 1; num <= total; num++)
    {
        square[row][col] = num;
        next_row = (row - 1 + n) % n;
        next_col = (col + 1) % n;
        if (square[next_row][next_col] != 0)
        {
            row = (row + 1) % n;
        }
        else
        {
            row = next_row;
            col = next_col;
        }
    }

    return square;
}

void free_magic_square(int **square, int n)
{
    int i;

    if (square == NULL)
    {
        return;
    }

    for (i = 0; i < n; i++)
    {
        free(square[i]);
    }
    free(square);
}

void print_magic_square(int **square, int n)
{
    int i;
    int j;

    if (square == NULL || n < 1)
    {
        return;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    char *end;
    long input;
    int n;
    int **square;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <odd_order>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(argv[1], &end, 10);
    if (errno == ERANGE || *end != '\0' || input < 1 || input > INT_MAX || input % 2 == 0)
    {
        fprintf(stderr, "Error: order must be a positive odd integer\n");
        return EXIT_FAILURE;
    }

    n = (int)input;
    square = generate_magic_square(n);
    if (square == NULL)
    {
        fprintf(stderr, "Error: unable to generate magic square\n");
        return EXIT_FAILURE;
    }

    print_magic_square(square, n);
    free_magic_square(square, n);

    return EXIT_SUCCESS;
}