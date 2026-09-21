#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t n_plus_one;
    uint64_t two_n_plus_one;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t total;
    uint64_t x;
    uint64_t y;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!add_u64(minimum, 1, &n_plus_one)) {
        return 0;
    }

    x = minimum;
    y = n_plus_one;

    if ((x & UINT64_C(1)) == 0) {
        x /= 2;
    } else {
        y /= 2;
    }

    if (!multiply_u64(x, y, &triangular)) {
        return 0;
    }

    if (minimum > (UINT64_MAX - 1) / 2) {
        return 0;
    }

    two_n_plus_one = minimum * 2 + 1;
    x = triangular;
    y = two_n_plus_one;

    if (x % 3 == 0) {
        x /= 3;
    } else if (y % 3 == 0) {
        y /= 3;
    } else {
        return 0;
    }

    if (!multiply_u64(x, y, &square_sum)) {
        return 0;
    }

    if (!add_u64(maximum, 1, &x)) {
        return 0;
    }

    if (!multiply_u64(triangular, x, &total) || total < square_sum) {
        return 0;
    }

    *result = total - square_sum;
    return 1;
}

static int read_dimensions(uint64_t *width, uint64_t *height)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *cursor;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[sizeof buffer - 2] != '\n' &&
        buffer[sizeof buffer - 2] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 0;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '+') {
        return 0;
    }

    errno = 0;
    {
        uintmax_t value = strtoumax(cursor, &end, 10);

        if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
            return 0;
        }

        *width = (uint64_t)value;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '+') {
        return 0;
    }

    errno = 0;
    {
        uintmax_t value = strtoumax(cursor, &end, 10);

        if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
            return 0;
        }

        *height = (uint64_t)value;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_dimensions(&width, &height)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}