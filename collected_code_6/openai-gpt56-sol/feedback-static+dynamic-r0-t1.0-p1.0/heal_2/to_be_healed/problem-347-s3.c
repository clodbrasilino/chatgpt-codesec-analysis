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
    if (result == NULL || (a != 0U && b > UINT64_MAX / a)) {
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
    uint64_t divisor;

    if (result == NULL || width == 0U || height == 0U) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!add_u64(minimum, 1U, &n_plus_one)) {
        return 0;
    }

    x = minimum;
    y = n_plus_one;

    if ((x & 1U) == 0U) {
        x /= 2U;
    } else {
        y /= 2U;
    }

    if (!multiply_u64(x, y, &triangular)) {
        return 0;
    }

    if (minimum > (UINT64_MAX - 1U) / 2U) {
        return 0;
    }

    two_n_plus_one = minimum * 2U + 1U;
    x = triangular;
    y = two_n_plus_one;
    divisor = 3U;

    if (x % divisor == 0U) {
        x /= divisor;
        divisor = 1U;
    }

    if (divisor != 1U && y % divisor == 0U) {
        y /= divisor;
        divisor = 1U;
    }

    if (divisor != 1U) {
        return 0;
    }

    if (!multiply_u64(x, y, &square_sum)) {
        return 0;
    }

    if (!add_u64(maximum, 1U, &x)) {
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

    if (width == NULL || height == NULL ||
        fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    *width = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        return 0;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    *height = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        return 0;
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