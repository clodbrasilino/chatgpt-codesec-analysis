#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    long double average;
    size_t length;
    size_t *rows;
    size_t *columns;
} PathResult;

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

static bool find_max_average_path(const long double *matrix,
                                  size_t n,
                                  PathResult *result)
{
    long double *dp = NULL;
    unsigned char *parents = NULL;
    size_t *rows = NULL;
    size_t *columns = NULL;
    size_t cell_count;
    size_t path_length;
    long double maximum_sum;
    size_t i;
    size_t j;

    if (result == NULL) {
        return false;
    }

    result->average = 0.0L;
    result->length = 0;
    result->rows = NULL;
    result->columns = NULL;

    if (matrix == NULL || n == 0 || n > SIZE_MAX / n) {
        return false;
    }

    cell_count = n * n;

    if (cell_count > SIZE_MAX / sizeof(*parents) ||
        n > SIZE_MAX / sizeof(*dp) ||
        n > SIZE_MAX / 2U + 1U) {
        return false;
    }

    path_length = n * 2U - 1U;

    if (path_length > SIZE_MAX / sizeof(*rows) ||
        path_length > SIZE_MAX / sizeof(*columns)) {
        return false;
    }

    dp = malloc(n * sizeof(*dp));
    parents = malloc(cell_count * sizeof(*parents));
    rows = malloc(path_length * sizeof(*rows));
    columns = malloc(path_length * sizeof(*columns));

    if (dp == NULL || parents == NULL || rows == NULL || columns == NULL) {
        free(dp);
        free(parents);
        free(rows);
        free(columns);
        return false;
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            size_t index = i * n + j;
            long double value = matrix[index];

            if (!isfinite(value)) {
                free(dp);
                free(parents);
                free(rows);
                free(columns);
                return false;
            }

            if (i == 0 && j == 0) {
                dp[j] = value;
                parents[index] = 0U;
            } else if (i == 0) {
                dp[j] = dp[j - 1U] + value;
                parents[index] = 1U;
            } else if (j == 0) {
                dp[j] = dp[j] + value;
                parents[index] = 2U;
            } else if (dp[j - 1U] >= dp[j]) {
                dp[j] = dp[j - 1U] + value;
                parents[index] = 1U;
            } else {
                dp[j] = dp[j] + value;
                parents[index] = 2U;
            }

            if (!isfinite(dp[j])) {
                free(dp);
                free(parents);
                free(rows);
                free(columns);
                return false;
            }
        }
    }

    maximum_sum = dp[n - 1U];
    i = n - 1U;
    j = n - 1U;

    for (size_t position = path_length; position > 0; ) {
        size_t index;

        --position;
        rows[position] = i;
        columns[position] = j;

        if (i == 0 && j == 0) {
            if (position != 0) {
                free(dp);
                free(parents);
                free(rows);
                free(columns);
                return false;
            }
            break;
        }

        index = i * n + j;

        if (parents[index] == 1U && j > 0) {
            --j;
        } else if (parents[index] == 2U && i > 0) {
            --i;
        } else {
            free(dp);
            free(parents);
            free(rows);
            free(columns);
            return false;
        }
    }

    free(dp);
    free(parents);

    result->average = maximum_sum / (long double)path_length;
    result->length = path_length;
    result->rows = rows;
    result->columns = columns;

    return true;
}

int main(void)
{
    size_t n;
    size_t cell_count;
    long double *matrix = NULL;
    PathResult result = {0.0L, 0U, NULL, NULL};

    if (scanf("%zu", &n) != 1 || n == 0 || n > SIZE_MAX / n) {
        fprintf(stderr, "Invalid matrix size\n");
        return EXIT_FAILURE;
    }

    cell_count = n * n;

    if (cell_count > SIZE_MAX / sizeof(*matrix)) {
        fprintf(stderr, "Matrix size is too large\n");
        return EXIT_FAILURE;
    }

    matrix = malloc(cell_count * sizeof(*matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < cell_count; ++i) {
        if (scanf("%Lf", &matrix[i]) != 1 || !isfinite(matrix[i])) {
            fprintf(stderr, "Invalid matrix element\n");
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    if (!find_max_average_path(matrix, n, &result)) {
        fprintf(stderr, "Unable to find a maximum-average path\n");
        free(matrix);
        return EXIT_FAILURE;
    }

    free(matrix);

    if (printf("Maximum average: %.10Lf\nPath:", result.average) < 0) {
        free_path_result(&result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.length; ++i) {
        if (printf(" (%zu,%zu)", result.rows[i], result.columns[i]) < 0) {
            free_path_result(&result);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free_path_result(&result);
        return EXIT_FAILURE;
    }

    free_path_result(&result);
    return EXIT_SUCCESS;
}