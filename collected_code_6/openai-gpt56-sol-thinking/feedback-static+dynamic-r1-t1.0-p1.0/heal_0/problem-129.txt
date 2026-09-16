#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void generate_odd_magic_square(size_t order, uint64_t *square)
{
    const size_t count = order * order;
    size_t row = 0;
    size_t column = order / 2;

    for (size_t placed = 0; placed < count; ++placed) {
        size_t next_row;
        size_t next_column;

        square[row * order + column] = (uint64_t)placed + 1U;
        next_row = (row + order - 1U) % order;
        next_column = (column + 1U) % order;

        if (square[next_row * order + next_column] != 0U) {
            row = (row + 1U) % order;
        } else {
            row = next_row;
            column = next_column;
        }
    }
}

static void generate_doubly_even_magic_square(size_t order, uint64_t *square)
{
    const size_t count = order * order;
    const uint64_t maximum = (uint64_t)count + 1U;

    for (size_t row = 0; row < order; ++row) {
        for (size_t column = 0; column < order; ++column) {
            const size_t index = row * order + column;
            const uint64_t value = (uint64_t)index + 1U;
            const size_t row_mod = row % 4U;
            const size_t column_mod = column % 4U;

            if (row_mod == column_mod || row_mod + column_mod == 3U) {
                square[index] = maximum - value;
            } else {
                square[index] = value;
            }
        }
    }
}

static int generate_singly_even_magic_square(size_t order, uint64_t *square)
{
    const size_t half = order / 2U;
    const size_t quadrant_size = half * half;
    const uint64_t offset = (uint64_t)quadrant_size;
    const size_t swap_count = (order - 2U) / 4U;
    uint64_t *quadrant = calloc(quadrant_size, sizeof(*quadrant));

    if (quadrant == NULL) {
        return -1;
    }

    generate_odd_magic_square(half, quadrant);

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = 0; column < half; ++column) {
            const uint64_t value = quadrant[row * half + column];

            square[row * order + column] = value;
            square[row * order + column + half] = value + 2U * offset;
            square[(row + half) * order + column] = value + 3U * offset;
            square[(row + half) * order + column + half] = value + offset;
        }
    }

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = 0; column < swap_count; ++column) {
            const size_t top = row * order + column;
            const size_t bottom = (row + half) * order + column;
            const uint64_t temporary = square[top];

            square[top] = square[bottom];
            square[bottom] = temporary;
        }
    }

    {
        const size_t middle_row = half / 2U;
        const size_t first_top = middle_row * order;
        const size_t first_bottom = (middle_row + half) * order;
        const size_t special_top = first_top + swap_count;
        const size_t special_bottom = first_bottom + swap_count;
        uint64_t temporary = square[first_top];

        square[first_top] = square[first_bottom];
        square[first_bottom] = temporary;

        temporary = square[special_top];
        square[special_top] = square[special_bottom];
        square[special_bottom] = temporary;
    }

    if (swap_count > 1U) {
        for (size_t row = 0; row < half; ++row) {
            for (size_t column = order - swap_count + 1U; column < order; ++column) {
                const size_t top = row * order + column;
                const size_t bottom = (row + half) * order + column;
                const uint64_t temporary = square[top];

                square[top] = square[bottom];
                square[bottom] = temporary;
            }
        }
    }

    free(quadrant);
    return 0;
}

static int calculate_magic_square(size_t order, uint64_t **result)
{
    size_t count;
    uint64_t *square;

    if (result == NULL || order == 0U || order == 2U) {
        return -1;
    }

    *result = NULL;

    if (order > SIZE_MAX / order || order > UINT64_MAX / order) {
        return -1;
    }

    count = order * order;

    if (count >= UINT64_MAX || count > SIZE_MAX / sizeof(*square)) {
        return -1;
    }

    square = calloc(count, sizeof(*square));
    if (square == NULL) {
        return -1;
    }

    if ((order % 2U) != 0U) {
        generate_odd_magic_square(order, square);
    } else if ((order % 4U) == 0U) {
        generate_doubly_even_magic_square(order, square);
    } else if (generate_singly_even_magic_square(order, square) != 0) {
        free(square);
        return -1;
    }

    *result = square;
    return 0;
}

static int print_magic_square(size_t order, const uint64_t *square)
{
    for (size_t row = 0; row < order; ++row) {
        for (size_t column = 0; column < order; ++column) {
            const char *separator = column + 1U == order ? "\n" : " ";

            if (printf("%" PRIu64 "%s",
                       square[row * order + column],
                       separator) < 0) {
                return -1;
            }
        }
    }

    return fflush(stdout) == 0 ? 0 : -1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_order;
    size_t order;
    uint64_t *square = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <order>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid order\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_order = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_order > SIZE_MAX) {
        fprintf(stderr, "Invalid order\n");
        return EXIT_FAILURE;
    }

    order = (size_t)parsed_order;

    if (calculate_magic_square(order, &square) != 0) {
        fprintf(stderr, "Unable to calculate a magic square of order %zu\n",
                order);
        return EXIT_FAILURE;
    }

    if (print_magic_square(order, square) != 0) {
        free(square);
        fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    free(square);
    return EXIT_SUCCESS;
}