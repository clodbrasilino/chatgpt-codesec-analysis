#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long double average;
    size_t length;
    size_t *rows;
    size_t *columns;
} PathResult;

typedef enum {
    PATH_SUCCESS = 0,
    PATH_INVALID_ARGUMENT,
    PATH_ALLOCATION_FAILURE,
    PATH_INVALID_VALUE,
    PATH_NUMERIC_ERROR
} PathStatus;

static void free_path_result(PathResult *result)
{
    if (result != NULL) {
        free(result->rows);
        free(result->columns);
        result->rows = NULL;
        result->columns = NULL;
        result->length = 0;
        result->average = 0.0L;
    }
}

static PathStatus find_max_average_path(const double *matrix,
                                        size_t n,
                                        PathResult *result)
{
    enum {
        DIRECTION_START = 0,
        DIRECTION_UP = 1,
        DIRECTION_LEFT = 2
    };

    size_t cell_count;
    size_t path_length;
    long double *best;
    unsigned char *directions;
    size_t i;
    size_t j;
    size_t k;

    if (matrix == NULL || result == NULL || n == 0) {
        return PATH_INVALID_ARGUMENT;
    }

    result->average = 0.0L;
    result->length = 0;
    result->rows = NULL;
    result->columns = NULL;

    if (n > SIZE_MAX / n) {
        return PATH_INVALID_ARGUMENT;
    }

    cell_count = n * n;

    if (n > SIZE_MAX / 2U + 1U) {
        return PATH_INVALID_ARGUMENT;
    }

    path_length = 2U * n - 1U;

    if (n > SIZE_MAX / sizeof(*best) ||
        cell_count > SIZE_MAX / sizeof(*directions) ||
        path_length > SIZE_MAX / sizeof(*result->rows) ||
        path_length > SIZE_MAX / sizeof(*result->columns)) {
        return PATH_INVALID_ARGUMENT;
    }

    for (k = 0; k < cell_count; ++k) {
        if (!isfinite(matrix[k])) {
            return PATH_INVALID_VALUE;
        }
    }

    best = malloc(n * sizeof(*best));
    directions = malloc(cell_count * sizeof(*directions));
    result->rows = malloc(path_length * sizeof(*result->rows));
    result->columns = malloc(path_length * sizeof(*result->columns));

    if (best == NULL || directions == NULL ||
        result->rows == NULL || result->columns == NULL) {
        free(best);
        free(directions);
        free_path_result(result);
        return PATH_ALLOCATION_FAILURE;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            long double value = (long double)matrix[i * n + j];
            long double previous;

            if (i == 0 && j == 0) {
                best[j] = value;
                directions[0] = DIRECTION_START;
                continue;
            }

            if (i == 0) {
                previous = best[j - 1U];
                directions[j] = DIRECTION_LEFT;
            } else if (j == 0) {
                previous = best[j];
                directions[i * n] = DIRECTION_UP;
            } else if (best[j] >= best[j - 1U]) {
                previous = best[j];
                directions[i * n + j] = DIRECTION_UP;
            } else {
                previous = best[j - 1U];
                directions[i * n + j] = DIRECTION_LEFT;
            }

            best[j] = previous + value;

            if (!isfinite(best[j])) {
                free(best);
                free(directions);
                free_path_result(result);
                return PATH_NUMERIC_ERROR;
            }
        }
    }

    result->average = best[n - 1U] / (long double)path_length;
    result->length = path_length;

    i = n - 1U;
    j = n - 1U;
    k = path_length;

    for (;;) {
        unsigned char direction;

        --k;
        result->rows[k] = i;
        result->columns[k] = j;

        if (i == 0 && j == 0) {
            break;
        }

        direction = directions[i * n + j];

        if (direction == DIRECTION_UP && i > 0) {
            --i;
        } else if (direction == DIRECTION_LEFT && j > 0) {
            --j;
        } else {
            free(best);
            free(directions);
            free_path_result(result);
            return PATH_NUMERIC_ERROR;
        }
    }

    free(best);
    free(directions);
    return PATH_SUCCESS;
}

int main(void)
{
    size_t n;
    size_t cell_count;
    size_t i;
    double *matrix;
    PathResult result;
    PathStatus status;

    result.average = 0.0L;
    result.length = 0;
    result.rows = NULL;
    result.columns = NULL;

    if (scanf("%zu", &n) != 1 || n == 0 || n > SIZE_MAX / n) {
        fprintf(stderr, "Invalid matrix size\n");
        return EXIT_FAILURE;
    }

    cell_count = n * n;

    if (cell_count > SIZE_MAX / sizeof(*matrix)) {
        fprintf(stderr, "Matrix is too large\n");
        return EXIT_FAILURE;
    }

    matrix = malloc(cell_count * sizeof(*matrix));

    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < cell_count; ++i) {
        if (scanf("%lf", &matrix[i]) != 1 || !isfinite(matrix[i])) {
            fprintf(stderr, "Invalid matrix value\n");
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    status = find_max_average_path(matrix, n, &result);
    free(matrix);

    if (status != PATH_SUCCESS) {
        fprintf(stderr, "Unable to find a path\n");
        free_path_result(&result);
        return EXIT_FAILURE;
    }

    printf("%.10Lf\n", result.average);

    for (i = 0; i < result.length; ++i) {
        printf("%zu %zu\n", result.rows[i], result.columns[i]);
    }

    free_path_result(&result);
    return EXIT_SUCCESS;
}