#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_magic_square(size_t order, uint64_t *square)
{
    if (square == NULL || order == 0U || order % 2U == 0U) {
        return -1;
    }

    size_t row = 0U;
    size_t column = order / 2U;
    const uint64_t limit = (uint64_t)order * (uint64_t)order;

    for (uint64_t value = 1U; value <= limit; ++value) {
        square[row * order + column] = value;

        const size_t next_row = row == 0U ? order - 1U : row - 1U;
        const size_t next_column =
            column == order - 1U ? 0U : column + 1U;

        if (square[next_row * order + next_column] != 0U) {
            row = row == order - 1U ? 0U : row + 1U;
        } else {
            row = next_row;
            column = next_column;
        }
    }

    return 0;
}

static int parse_order(const char *text, size_t *order)
{
    if (text == NULL || order == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value == 0U || value % 2U == 0U ||
        value > SIZE_MAX ||
        value > UINT64_MAX / value ||
        value > SIZE_MAX / value) {
        return -1;
    }

    const size_t converted = (size_t)value;
    const size_t element_count = converted * converted;

    if (element_count > SIZE_MAX / sizeof(uint64_t)) {
        return -1;
    }

    *order = converted;
    return 0;
}

static int decimal_width_u64(uint64_t value)
{
    int width = 1;

    while (value >= UINT64_C(10)) {
        value /= UINT64_C(10);
        ++width;
    }

    return width;
}

static int print_magic_square(const uint64_t *square, size_t order)
{
    if (square == NULL || order == 0U ||
        order > UINT64_MAX / order ||
        order > SIZE_MAX / order) {
        return -1;
    }

    const uint64_t maximum = (uint64_t)order * (uint64_t)order;
    const int width = decimal_width_u64(maximum);

    for (size_t row = 0U; row < order; ++row) {
        const size_t row_offset = row * order;

        for (size_t column = 0U; column < order; ++column) {
            const char separator =
                column == order - 1U ? '\n' : ' ';

            if (printf("%*" PRIu64 "%c",
                       width,
                       square[row_offset + column],
                       separator) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program_name = "magic_square";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <positive-odd-order>\n", program_name);
        return EXIT_FAILURE;
    }

    size_t order = 0U;

    if (parse_order(argv[1], &order) != 0) {
        fputs("Order must be a positive odd integer of supported size.\n",
              stderr);
        return EXIT_FAILURE;
    }

    const size_t element_count = order * order;
    uint64_t *square = calloc(element_count, sizeof(*square));

    if (square == NULL) {
        fputs("Unable to allocate memory for the magic square.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    if (calculate_magic_square(order, square) != 0 ||
        print_magic_square(square, order) != 0) {
        fputs("Unable to calculate or print the magic square.\n", stderr);
        status = EXIT_FAILURE;
    }

    free(square);
    return status;
}