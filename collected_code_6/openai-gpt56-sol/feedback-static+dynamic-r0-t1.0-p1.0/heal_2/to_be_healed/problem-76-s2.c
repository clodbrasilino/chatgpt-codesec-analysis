#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int triangular_u64(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;

    if (!add_u64(n, 1, &b)) {
        return 0;
    }

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    return multiply_u64(a, b, result);
}

static int sum_squares_u64(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;
    uint64_t c;

    if (!add_u64(n, 1, &b) || !add_u64(n, n, &c) ||
        !add_u64(c, 1, &c)) {
        return 0;
    }

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a % 3U == 0) {
        a /= 3;
    } else if (b % 3U == 0) {
        b /= 3;
    } else {
        c /= 3;
    }

    if (!multiply_u64(a, b, &a)) {
        return 0;
    }

    return multiply_u64(a, c, result);
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t triangular;
    uint64_t squares;
    uint64_t product;
    uint64_t adjustment;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    side = width < height ? width : height;
    other = width < height ? height : width;

    if (!triangular_u64(side, &triangular) ||
        !sum_squares_u64(side, &squares) ||
        !multiply_u64(other, triangular, &product)) {
        return 0;
    }

    adjustment = squares - triangular;

    if (product < adjustment) {
        return 0;
    }

    *result = product - adjustment;
    return 1;
}

static int parse_dimensions(const char *line, uint64_t *width, uint64_t *height)
{
    char *end;
    const char *cursor = line;
    uintmax_t first;
    uintmax_t second;

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *width = (uint64_t)first;
    *height = (uint64_t)second;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (fgets(line, sizeof line, stdin) == NULL ||
        parse_dimensions(line, &width, &height) == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}