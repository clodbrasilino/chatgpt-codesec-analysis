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
            column + 1U == order ? 0U : column + 1U;

        if (square[next_row * order + next_column] != 0U) {
            row = row + 1U == order ? 0U : row + 1U;
        } else {
            row = next_row;
            column = next_column;
        }
    }

    return 0;
}

static int parse_order(const char *text, size_t *order)
{
    if (text == NULL || order == NULL || *text == '\0' || *text == '-') {
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

static int print_magic_square(const uint64_t *square, size_t order)
{
    if (square == NULL || order == 0U) {
        return -1;
    }

    const uint64_t maximum = (uint64_t)order * (uint64_t)order;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char maximum_text[sizeof(uint64_t) * 3U + 1U];

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    const int width = snprintf(maximum_text, sizeof(maximum_text),
                               "%" PRIu64, maximum);

    if (width < 0 || (size_t)width >= sizeof(maximum_text)) {
        return -1;
    }

    for (size_t row = 0U; row < order; ++row) {
        for (size_t column = 0U; column < order; ++column) {
            const char separator = column + 1U == order ? '\n' : ' ';

            if (printf("%*" PRIu64 "%c",
                       width,
                       square[row * order + column],
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
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "magic_square";

        fprintf(stderr, "Usage: %s <positive-odd-order>\n", program_name);
        return EXIT_FAILURE;
    }

    const char *const order_text = argv[1];
    size_t order = 0U;

    if (parse_order(order_text, &order) != 0) {
        fprintf(stderr,
                "Order must be a positive odd integer of supported size.\n");
        return EXIT_FAILURE;
    }

    const size_t element_count = order * order;
    uint64_t *square = calloc(element_count, sizeof(*square));

    if (square == NULL) {
        fprintf(stderr, "Unable to allocate memory for the magic square.\n");
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    if (calculate_magic_square(order, square) != 0 ||
        print_magic_square(square, order) != 0) {
        fprintf(stderr, "Unable to calculate or print the magic square.\n");
        status = EXIT_FAILURE;
    }

    free(square);
    return status;
}