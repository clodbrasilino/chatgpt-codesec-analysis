#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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

static int flatten_columns(const int *matrix, size_t rows, size_t columns,
                           Tuple **output, size_t *output_count)
{
    Tuple *tuples = NULL;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (rows == 0 || columns == 0) {
        return 0;
    }

    if (matrix == NULL ||
        columns > SIZE_MAX / sizeof(*tuples) ||
        rows > SIZE_MAX / sizeof(int) ||
        rows > SIZE_MAX / columns) {
        return -1;
    }

    tuples = calloc(columns, sizeof(*tuples));
    if (tuples == NULL) {
        return -1;
    }

    for (size_t column = 0; column < columns; ++column) {
        tuples[column].values = malloc(rows * sizeof(*tuples[column].values));
        if (tuples[column].values == NULL) {
            free_tuple_list(tuples, columns);
            return -1;
        }

        tuples[column].length = rows;

        for (size_t row = 0; row < rows; ++row) {
            tuples[column].values[row] = matrix[row * columns + column];
        }
    }

    *output = tuples;
    *output_count = columns;
    return 0;
}

int main(void)
{
    const int matrix[][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    const size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    const size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    Tuple *tuples = NULL;
    size_t tuple_count = 0;

    if (flatten_columns(&matrix[0][0], rows, columns,
                        &tuples, &tuple_count) != 0) {
        fputs("Failed to flatten matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (putchar('(') == EOF) {
            free_tuple_list(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%d%s", tuples[i].values[j],
                       j + 1 < tuples[i].length ? ", " : "") < 0) {
                free_tuple_list(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }

        if (puts(")") == EOF) {
            free_tuple_list(tuples, tuple_count);
            return EXIT_FAILURE;
        }
    }

    free_tuple_list(tuples, tuple_count);
    return EXIT_SUCCESS;
}