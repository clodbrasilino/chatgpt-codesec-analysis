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
    int num;
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

    for (int i = 0; i < n; i++)
    {
        square[i] = calloc((size_t)n, sizeof(*square[i]));
        if (square[i] == NULL)
        {
            for (int j = 0; j < i; j++)
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
        int next_row;
        int next_col;

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
    if (square == NULL)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        free(square[i]);
    }
    free(square);
}

void print_magic_square(int **square, int n)
{
    if (square == NULL || n < 1)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%4d", square[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
{
    /* Possible weaknesses found:
     *  expected '}'
     *  expected identifier or '(' at end of input
     *  expected identifier or '('
     *  expected declaration or statement at end of input
     */
    char *