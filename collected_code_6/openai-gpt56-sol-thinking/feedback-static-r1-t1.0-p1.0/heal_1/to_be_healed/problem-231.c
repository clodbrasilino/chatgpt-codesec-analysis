#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRIANGLE_SUCCESS,
    TRIANGLE_INVALID_ARGUMENT,
    TRIANGLE_INPUT_ERROR,
    TRIANGLE_ALLOCATION_ERROR,
    TRIANGLE_OVERFLOW
} TriangleStatus;

static int add_int64_checked(int64_t left, int64_t right, int64_t *result)
{
    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static TriangleStatus find_maximum_sum(FILE *input, size_t rows, int64_t *result)
{
    int64_t *previous;
    int64_t *current;
    size_t row;
    size_t column;

    if (input == NULL || result == NULL || rows == 0) {
        return TRIANGLE_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / sizeof(*previous)) {
        return TRIANGLE_ALLOCATION_ERROR;
    }

    previous = malloc(rows * sizeof(*previous));
    current = malloc(rows * sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return TRIANGLE_ALLOCATION_ERROR;
    }

    for (row = 0; row < rows; ++row) {
        for (column = 0; column <= row; ++column) {
            int64_t value;
            int64_t parent;

            /* Possible weaknesses found:
             * Flawfinder fscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
             */
            if (fscanf(input, "%" SCNd64, &value) != 1) {
                free(previous);
                free(current);
                return TRIANGLE_INPUT_ERROR;
            }

            if (row == 0) {
                current[column] = value;
                continue;
            }

            if (column == 0) {
                parent = previous[0];
            } else if (column == row) {
                parent = previous[column - 1];
            } else {
                parent = previous[column - 1] > previous[column]
                             ? previous[column - 1]
                             : previous[column];
            }

            if (!add_int64_checked(parent, value, &current[column])) {
                free(previous);
                free(current);
                return TRIANGLE_OVERFLOW;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *result = previous[0];

    for (column = 1; column < rows; ++column) {
        if (previous[column] > *result) {
            *result = previous[column];
        }
    }

    free(previous);
    free(current);
    return TRIANGLE_SUCCESS;
}

int main(void)
{
    size_t rows;
    int64_t maximum_sum;
    TriangleStatus status;

    if (scanf("%zu", &rows) != 1 || rows == 0) {
        fputs("Invalid triangle size\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_maximum_sum(stdin, rows, &maximum_sum);

    if (status != TRIANGLE_SUCCESS) {
        switch (status) {
            case TRIANGLE_INPUT_ERROR:
                fputs("Invalid triangle data\n", stderr);
                break;
            case TRIANGLE_ALLOCATION_ERROR:
                fputs("Memory allocation failed\n", stderr);
                break;
            case TRIANGLE_OVERFLOW:
                fputs("Integer overflow\n", stderr);
                break;
            default:
                fputs("Invalid argument\n", stderr);
                break;
        }
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}