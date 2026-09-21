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

    for (size_t index = 0; index < cells; ++index) {
        size_t next_row;
        size_t next_column;

        square[row * n + column] = (uint64_t)index + UINT64_C(1);

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
            size_t row_mod = row % 4;
            size_t column_mod = column % 4;
            uint64_t value = (uint64_t)index + UINT64_C(1);

            if (row_mod == column_mod || row_mod + column_mod == 3) {
                value = (uint64_t)cells - (uint64_t)index;
            }

            square[index] = value;
        }
    }
}

static void swap_values(uint64_t *first, uint64_t *second)
{
    uint64_t temporary = *first;
    *first = *second;
    *second = temporary;
}

static int generate_singly_even_square(uint64_t *square, size_t n)
{
    size_t half = n / 2;
    size_t quadrant_cells = half * half;
    size_t swap_columns = (half - 1) / 2;
    uint64_t quadrant_offset = (uint64_t)quadrant_cells;
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
                value + UINT64_C(2) * quadrant_offset;
            square[(row + half) * n + column] =
                value + UINT64_C(3) * quadrant_offset;
            square[(row + half) * n + column + half] =
                value + quadrant_offset;
        }
    }

    free(odd_square);

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = 0; column < swap_columns; ++column) {
            size_t top = row * n + column;
            size_t bottom = (row + half) * n + column;

            swap_values(&square[top], &square[bottom]);
        }
    }

    for (size_t row = 0; row < half; ++row) {
        for (size_t column = half - swap_columns + 1;
             column < half;
             ++column) {
            size_t top = row * n + column + half;
            size_t bottom = (row + half) * n + column + half;

            swap_values(&square[top], &square[bottom]);
        }
    }

    {
        size_t top = swap_columns * n;
        size_t bottom = (swap_columns + half) * n;

        swap_values(&square[top], &square[bottom]);
    }

    {
        size_t top = swap_columns * n + swap_columns;
        size_t bottom = (swap_columns + half) * n + swap_columns;

        swap_values(&square[top], &square[bottom]);
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

    if (cells > UINT64_MAX ||
        cells > SIZE_MAX / sizeof(*square)) {
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

static int write_uint64(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    size_t position = sizeof(buffer);

    do {
        uint64_t quotient = value / UINT64_C(10);
        uint64_t remainder = value % UINT64_C(10);

        buffer[--position] = (char)('0' + remainder);
        value = quotient;
    } while (value != 0);

    return fwrite(buffer + position, 1, sizeof(buffer) - position, stdout) ==
                   sizeof(buffer) - position
               ? 0
               : -1;
}

static int print_magic_square(const uint64_t *square, size_t n)
{
    for (size_t row = 0; row < n; ++row) {
        for (size_t column = 0; column < n; ++column) {
            if (column != 0 && fputc(' ', stdout) == EOF) {
                return -1;
            }

            if (write_uint64(square[row * n + column]) != 0) {
                return -1;
            }
        }

        if (fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return fflush(stdout) == EOF ? -1 : 0;
}

static int is_decimal_number(const char *text)
{
    if (text == NULL || *text == '\0') {
        return 0;
    }

    while (*text != '\0') {
        if (*text < '0' || *text > '9') {
            return 0;
        }

        ++text;
    }

    return 1;
}

static void print_usage(const char *program_name)
{
    fputs("Usage: ", stderr);

    if (program_name != NULL && *program_name != '\0') {
        fputs(program_name, stderr);
    } else {
        fputs("magic-square", stderr);
    }

    fputs(" <order>\n", stderr);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    size_t n;
    uint64_t *square = NULL;
    int status;

    if (argc != 2) {
        print_usage(argc > 0 ? argv[0] : NULL);
        return EXIT_FAILURE;
    }

    if (!is_decimal_number(argv[1])) {
        fputs("Invalid order\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed > SIZE_MAX) {
        fputs("Invalid order\n", stderr);
        return EXIT_FAILURE;
    }

    n = (size_t)parsed;
    status = calculate_magic_square(n, &square);

    if (status != MAGIC_SQUARE_OK) {
        if (status == MAGIC_SQUARE_INVALID_SIZE) {
            fputs("The order must be 1 or greater than 2\n", stderr);
        } else if (status == MAGIC_SQUARE_TOO_LARGE) {
            fputs("The requested square is too large\n", stderr);
        } else {
            fputs("Unable to allocate memory\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (print_magic_square(square, n) != 0) {
        free(square);
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    free(square);
    return EXIT_SUCCESS;
}