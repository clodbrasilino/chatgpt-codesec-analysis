#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GOLD_OK,
    GOLD_INVALID_ARGUMENT,
    GOLD_ALLOCATION_FAILURE,
    GOLD_ARITHMETIC_OVERFLOW
} GoldStatus;

static bool add_int64_checked(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

GoldStatus solve_gold_mine(const int64_t *mine,
                           size_t rows,
                           size_t columns,
                           int64_t *maximum_gold)
{
    int64_t *previous;
    int64_t *current;
    int64_t *temporary;

    if (mine == NULL || maximum_gold == NULL || rows == 0 || columns == 0) {
        return GOLD_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / columns ||
        rows > SIZE_MAX / sizeof(*previous)) {
        return GOLD_INVALID_ARGUMENT;
    }

    previous = malloc(rows * sizeof(*previous));
    if (previous == NULL) {
        return GOLD_ALLOCATION_FAILURE;
    }

    current = malloc(rows * sizeof(*current));
    if (current == NULL) {
        free(previous);
        return GOLD_ALLOCATION_FAILURE;
    }

    for (size_t row = 0; row < rows; ++row) {
        previous[row] = mine[row * columns];
    }

    for (size_t column = 1; column < columns; ++column) {
        for (size_t row = 0; row < rows; ++row) {
            int64_t best = previous[row];

            if (row > 0 && previous[row - 1] > best) {
                best = previous[row - 1];
            }

            if (row < rows - 1 && previous[row + 1] > best) {
                best = previous[row + 1];
            }

            if (!add_int64_checked(best,
                                   mine[row * columns + column],
                                   &current[row])) {
                free(current);
                free(previous);
                return GOLD_ARITHMETIC_OVERFLOW;
            }
        }

        temporary = previous;
        previous = current;
        current = temporary;
    }

    *maximum_gold = previous[0];

    for (size_t row = 1; row < rows; ++row) {
        if (previous[row] > *maximum_gold) {
            *maximum_gold = previous[row];
        }
    }

    free(current);
    free(previous);
    return GOLD_OK;
}

int main(void)
{
    size_t rows;
    size_t columns;
    size_t cell_count;
    int64_t *mine;
    int64_t maximum_gold;
    GoldStatus status;

    if (scanf("%zu %zu", &rows, &columns) != 2 || rows == 0 || columns == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / columns) {
        fputs("Matrix dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    cell_count = rows * columns;

    if (cell_count > SIZE_MAX / sizeof(*mine)) {
        fputs("Matrix dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(cell_count * sizeof(*mine));
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < cell_count; ++index) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &mine[index]) != 1) {
            fputs("Invalid matrix data\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    status = solve_gold_mine(mine, rows, columns, &maximum_gold);
    free(mine);

    if (status == GOLD_ALLOCATION_FAILURE) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == GOLD_ARITHMETIC_OVERFLOW) {
        fputs("Arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != GOLD_OK) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_gold);
    return EXIT_SUCCESS;
}