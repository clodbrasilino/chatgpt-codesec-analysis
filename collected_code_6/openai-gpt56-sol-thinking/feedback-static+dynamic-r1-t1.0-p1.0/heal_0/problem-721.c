#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    size_t length;
    size_t *rows;
    size_t *columns;
    long double average;
} PathResult;

static void destroy_path_result(PathResult *result)
{
    if (result != NULL) {
        free(result->rows);
        free(result->columns);
        free(result);
    }
}

static PathResult *find_max_average_path(const long double *matrix, size_t n)
{
    size_t cell_count;
    size_t path_length;
    long double *averages = NULL;
    unsigned char *parents = NULL;
    PathResult *result = NULL;

    if (matrix == NULL || n == 0) {
        return NULL;
    }

    if (n > SIZE_MAX / n) {
        return NULL;
    }

    cell_count = n * n;

    if (n > SIZE_MAX / 2 + 1) {
        return NULL;
    }

    path_length = 2 * n - 1;

    if (n > SIZE_MAX / sizeof(*averages) ||
        path_length > SIZE_MAX / sizeof(*result->rows)) {
        return NULL;
    }

    averages = malloc(n * sizeof(*averages));
    parents = malloc(cell_count * sizeof(*parents));

    if (averages == NULL || parents == NULL) {
        free(averages);
        free(parents);
        return NULL;
    }

    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            size_t index = row * n + column;
            long double value = matrix[index];
            long double previous_average;
            long double current_length;

            if (!isfinite(value)) {
                free(averages);
                free(parents);
                return NULL;
            }

            if (row == 0 && column == 0) {
                averages[column] = value;
                parents[index] = 0;
                continue;
            }

            if (row == 0) {
                previous_average = averages[column - 1];
                parents[index] = 2;
            } else if (column == 0) {
                previous_average = averages[column];
                parents[index] = 1;
            } else if (averages[column] >= averages[column - 1]) {
                previous_average = averages[column];
                parents[index] = 1;
            } else {
                previous_average = averages[column - 1];
                parents[index] = 2;
            }

            current_length = (long double)(row + column + 1);
            averages[column] =
                previous_average * ((current_length - 1.0L) / current_length) +
                value / current_length;

            if (!isfinite(averages[column])) {
                free(averages);
                free(parents);
                return NULL;
            }
        }
    }

    result = malloc(sizeof(*result));

    if (result == NULL) {
        free(averages);
        free(parents);
        return NULL;
    }

    result->rows = malloc(path_length * sizeof(*result->rows));
    result->columns = malloc(path_length * sizeof(*result->columns));
    result->length = path_length;
    result->average = averages[n - 1];

    if (result->rows == NULL || result->columns == NULL) {
        free(averages);
        free(parents);
        destroy_path_result(result);
        return NULL;
    }

    {
        size_t row = n - 1;
        size_t column = n - 1;
        size_t position = path_length;

        while (position > 0) {
            size_t index;

            --position;
            result->rows[position] = row;
            result->columns[position] = column;

            if (row == 0 && column == 0) {
                break;
            }

            index = row * n + column;

            if (parents[index] == 1 && row > 0) {
                --row;
            } else if (parents[index] == 2 && column > 0) {
                --column;
            } else {
                free(averages);
                free(parents);
                destroy_path_result(result);
                return NULL;
            }
        }

        if (position != 0 || row != 0 || column != 0) {
            free(averages);
            free(parents);
            destroy_path_result(result);
            return NULL;
        }
    }

    free(averages);
    free(parents);
    return result;
}

int main(void)
{
    size_t n;
    size_t cell_count;
    long double *matrix;
    PathResult *result;

    if (scanf("%zu", &n) != 1 || n == 0) {
        fputs("Invalid matrix size\n", stderr);
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / n) {
        fputs("Matrix size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    cell_count = n * n;

    if (cell_count > SIZE_MAX / sizeof(*matrix)) {
        fputs("Matrix size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    matrix = malloc(cell_count * sizeof(*matrix));

    if (matrix == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < cell_count; ++i) {
        if (scanf("%Lf", &matrix[i]) != 1 || !isfinite(matrix[i])) {
            fputs("Invalid matrix element\n", stderr);
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    result = find_max_average_path(matrix, n);
    free(matrix);

    if (result == NULL) {
        fputs("Unable to find a path\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.10Lf\n", result->average);

    for (size_t i = 0; i < result->length; ++i) {
        printf("(%zu,%zu)%c",
               result->rows[i],
               result->columns[i],
               i + 1 == result->length ? '\n' : ' ');
    }

    destroy_path_result(result);
    return EXIT_SUCCESS;
}