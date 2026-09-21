#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool calculate_magic_square(size_t order, uint64_t **result)
{
    uint64_t *square;
    size_t cells;
    size_t row;
    size_t column;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (order == 0U || order % 2U == 0U) {
        return false;
    }

    if (order > SIZE_MAX / order) {
        return false;
    }

    cells = order * order;

    if (cells > SIZE_MAX / sizeof(*square) ||
        (uintmax_t)cells > (uintmax_t)UINT64_MAX) {
        return false;
    }

    square = calloc(cells, sizeof(*square));
    if (square == NULL) {
        return false;
    }

    row = 0U;
    column = order / 2U;

    for (size_t index = 0U; index < cells; ++index) {
        size_t next_row;
        size_t next_column;

        square[row * order + column] = (uint64_t)index + UINT64_C(1);

        next_row = row == 0U ? order - 1U : row - 1U;
        next_column = column + 1U == order ? 0U : column + 1U;

        if (square[next_row * order + next_column] != UINT64_C(0)) {
            row = row + 1U == order ? 0U : row + 1U;
        } else {
            row = next_row;
            column = next_column;
        }
    }

    *result = square;
    return true;
}

static bool write_uint64(FILE *stream, uint64_t value)
{
    char digits[20];
    size_t length = 0U;

    if (stream == NULL) {
        return false;
    }

    do {
        digits[length++] = (char)('0' + value % UINT64_C(10));
        value /= UINT64_C(10);
    } while (value != UINT64_C(0));

    while (length > 0U) {
        --length;

        if (fputc((unsigned char)digits[length], stream) == EOF) {
            return false;
        }
    }

    return true;
}

static bool print_magic_square(const uint64_t *square, size_t order)
{
    if (square == NULL || order == 0U || order > SIZE_MAX / order) {
        return false;
    }

    for (size_t row = 0U; row < order; ++row) {
        for (size_t column = 0U; column < order; ++column) {
            if (column != 0U && fputc(' ', stdout) == EOF) {
                return false;
            }

            if (!write_uint64(stdout, square[row * order + column])) {
                return false;
            }
        }

        if (fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return fflush(stdout) == 0;
}

static int fail(const char *message)
{
    if (message != NULL) {
        (void)fputs(message, stderr);
        (void)fflush(stderr);
    }

    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed_order;
    size_t order;
    uint64_t *square = NULL;

    if (argc != 2) {
        return fail("Usage: magic_square <positive odd order>\n");
    }

    if (argv[1] == NULL || argv[1][0] < '0' || argv[1][0] > '9') {
        return fail("The order must be a positive odd integer.\n");
    }

    errno = 0;
    parsed_order = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        parsed_order == UINTMAX_C(0) ||
        parsed_order > (uintmax_t)SIZE_MAX ||
        parsed_order % UINTMAX_C(2) == UINTMAX_C(0)) {
        return fail("The order must be a positive odd integer.\n");
    }

    order = (size_t)parsed_order;

    if (!calculate_magic_square(order, &square)) {
        return fail("Unable to calculate the magic square.\n");
    }

    if (!print_magic_square(square, order)) {
        free(square);
        return fail("Unable to write the magic square.\n");
    }

    free(square);
    return EXIT_SUCCESS;
}