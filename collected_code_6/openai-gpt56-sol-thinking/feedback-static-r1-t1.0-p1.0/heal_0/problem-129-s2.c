#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum MagicSquareResult {
    MAGIC_SQUARE_OK = 0,
    MAGIC_SQUARE_INVALID_SIZE,
    MAGIC_SQUARE_TOO_LARGE,
    MAGIC_SQUARE_NO_MEMORY
};

static void generate_odd_square(uint64_t *square, size_t n)
{
    size_t row = 0;
    size_t column = n / 2;
    size_t cells = n * n;

    for (size_t value = 1; value <= cells; ++value) {
        size_t next_row;
        size_t next_column;

        square[row * n + column] = (uint64_t)value;
        next_row = row == 0 ? n - 1 : row - 1;
        next_column = column + 1 == n ? 0 : column + 1;

        if (square[next_row * n + next_column] != 0) {
            row = row + 1 == n ? 0 : row + 1;
        } else {
            row = next_row;
            column = next_column;
        }
    }
}

static void generate_doubly_even_square(uint64_t *square, size_t n)
{
    size_t cells = n * n;

    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            size_t index = row * n + column;
            uint64_t value = (uint64_t)(index + 1);
            size_t row_mod = row % 4;
            size_t column_mod = column % 4;

            if (row_mod == column_mod || row_mod + column_mod == 3) {
                value = (uint64_t)(cells + 1) - value;
            }

            square[index] = value;
        }
    }
}

static int generate_singly_even_square(uint64_t *square, size_t n)
{
    size_t half = n / 2;
    size_t quadrant_cells = half * half;
    size_t swap_columns = (half - 1) / 2;
    uint64_t *odd_square = calloc(quadrant_cells, sizeof(*odd_square));

    if (odd_square == NULL) {
        return MAGIC_SQUARE_NO_MEMORY;
    }

    generate_odd_square(odd_square, half);

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = 0; column < half; ++column) {
            uint64_t value = odd_square[row * half + column];

            square[row * n + column] = value;
            square[row * n + column + half] =
                value + (uint64_t)(2 * quadrant_cells);
            square[(row + half) * n + column] =
                value + (uint64_t)(3 * quadrant_cells);
            square[(row + half) * n + column + half] =
                value + (uint64_t)quadrant_cells;
        }
    }

    free(odd_square);

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = 0; column < swap_columns; ++column) {
            size_t top = row * n + column;
            size_t bottom = (row + half) * n + column;
            uint64_t temporary = square[top];

            square[top] = square[bottom];
            square[bottom] = temporary;
        }
    }

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = half - swap_columns + 1;
             column < half;
             ++column) {
            size_t top = row * n + column + half;
            size_t bottom = (row + half) * n + column + half;
            uint64_t temporary = square[top];

            square[top] = square[bottom];
            square[bottom] = temporary;
        }
    }

    {
        size_t top = swap_columns * n;
        size_t bottom = (swap_columns + half) * n;
        uint64_t temporary = square[top];

        square[top] = square[bottom];
        square[bottom] = temporary;
    }

    {
        size_t top = swap_columns * n + swap_columns;
        size_t bottom = (swap_columns + half) * n + swap_columns;
        uint64_t temporary = square[top];

        square[top] = square[bottom];
        square[bottom] = temporary;
    }

    return MAGIC_SQUARE_OK;
}

int calculate_magic_square(size_t n, uint64_t **result)
{
    size_t cells;
    uint64_t *square;
    int status = MAGIC_SQUARE_OK;

    if (result == NULL) {
        return MAGIC_SQUARE_INVALID_SIZE;
    }

    *result = NULL;

    if (n == 0 || n == 2) {
        return MAGIC_SQUARE_INVALID_SIZE;
    }

    if (n > SIZE_MAX / n) {
        return MAGIC_SQUARE_TOO_LARGE;
    }

    cells = n * n;

    if (cells > SIZE_MAX / sizeof(*square)) {
        return MAGIC_SQUARE_TOO_LARGE;
    }

    square = calloc(cells, sizeof(*square));

    if (square == NULL) {
        return MAGIC_SQUARE_NO_MEMORY;
    }

    if ((n % 2) != 0) {
        generate_odd_square(square, n);
    } else if ((n % 4) == 0) {
        generate_doubly_even_square(square, n);
    } else {
        status = generate_singly_even_square(square, n);
    }

    if (status != MAGIC_SQUARE_OK) {
        free(square);
        return status;
    }

    *result = square;
    return MAGIC_SQUARE_OK;
}

static int print_magic_square(const uint64_t *square, size_t n)
{
    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            if (column != 0 && putchar(' ') == EOF) {
                return -1;
            }

            if (printf("%" PRIu64, square[row * n + column]) < 0) {
                return -1;
            }
        }

        if (putchar('\n') == EOF) {
            return -1;
        }
    }

    return fflush(stdout) == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    size_t n;
    uint64_t *square = NULL;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <order>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid order\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed > SIZE_MAX) {
        fprintf(stderr, "Invalid order\n");
        return EXIT_FAILURE;
    }

    n = (size_t)parsed;
    status = calculate_magic_square(n, &square);

    if (status != MAGIC_SQUARE_OK) {
        if (status == MAGIC_SQUARE_INVALID_SIZE) {
            fprintf(stderr, "The order must be 1 or greater than 2\n");
        } else if (status == MAGIC_SQUARE_TOO_LARGE) {
            fprintf(stderr, "The requested square is too large\n");
        } else {
            fprintf(stderr, "Unable to allocate memory\n");
        }

        return EXIT_FAILURE;
    }

    if (print_magic_square(square, n) != 0) {
        free(square);
        fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    free(square);
    return EXIT_SUCCESS;
}