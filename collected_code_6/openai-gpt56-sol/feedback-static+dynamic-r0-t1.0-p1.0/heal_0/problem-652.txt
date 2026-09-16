#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int flatten_columns(const Tuple *matrix, size_t rows, size_t cols,
                           Tuple **output, size_t *output_count)
{
    Tuple *result;
    size_t count;
    size_t index = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (rows == 0 || cols == 0) {
        return 0;
    }

    if (matrix == NULL || rows > SIZE_MAX / cols) {
        return -1;
    }

    count = rows * cols;

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t col = 0; col < cols; ++col) {
        for (size_t row = 0; row < rows; ++row) {
            result[index++] = matrix[row * cols + col];
        }
    }

    *output = result;
    *output_count = count;
    return 0;
}

int main(void)
{
    const size_t rows = 3;
    const size_t cols = 2;
    const Tuple matrix[] = {
        {1, 2}, {3, 4},
        {5, 6}, {7, 8},
        {9, 10}, {11, 12}
    };
    Tuple *list = NULL;
    size_t count = 0;

    if (flatten_columns(matrix, rows, cols, &list, &count) != 0) {
        fputs("Failed to flatten matrix.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)%c",
                   list[i].first,
                   list[i].second,
                   (i + 1 == count) ? '\n' : ' ') < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    free(list);
    return EXIT_SUCCESS;
}