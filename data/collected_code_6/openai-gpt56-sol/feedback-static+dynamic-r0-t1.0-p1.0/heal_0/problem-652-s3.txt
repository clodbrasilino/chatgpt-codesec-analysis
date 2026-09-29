#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

static void free_tuple_list(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].values);
    }

    free(tuples);
}

static Tuple *flatten_columns(const int *matrix, size_t rows, size_t columns)
{
    if (matrix == NULL || rows == 0 || columns == 0) {
        return NULL;
    }

    if (columns > SIZE_MAX / sizeof(Tuple) ||
        rows > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    Tuple *tuples = calloc(columns, sizeof(*tuples));
    if (tuples == NULL) {
        return NULL;
    }

    for (size_t column = 0; column < columns; ++column) {
        tuples[column].values = malloc(rows * sizeof(*tuples[column].values));
        if (tuples[column].values == NULL) {
            free_tuple_list(tuples, columns);
            return NULL;
        }

        tuples[column].length = rows;

        for (size_t row = 0; row < rows; ++row) {
            tuples[column].values[row] = matrix[row * columns + column];
        }
    }

    return tuples;
}

int main(void)
{
    const int matrix[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };
    const size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    const size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    Tuple *tuples = flatten_columns(&matrix[0][0], rows, columns);
    if (tuples == NULL) {
        fputs("Failed to flatten matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t column = 0; column < columns; ++column) {
        putchar('(');

        for (size_t row = 0; row < tuples[column].length; ++row) {
            if (printf("%d%s", tuples[column].values[row],
                       row + 1 < tuples[column].length ? ", " : "") < 0) {
                free_tuple_list(tuples, columns);
                return EXIT_FAILURE;
            }
        }

        if (puts(")") == EOF) {
            free_tuple_list(tuples, columns);
            return EXIT_FAILURE;
        }
    }

    free_tuple_list(tuples, columns);
    return EXIT_SUCCESS;
}