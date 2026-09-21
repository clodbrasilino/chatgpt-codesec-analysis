#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

static int checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
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
    uint64_t minimum_plus_one;
    uint64_t maximum_plus_one;
    uint64_t twice_minimum;
    uint64_t factor1;
    uint64_t factor2;
    uint64_t factor3;
    uint64_t sum;
    uint64_t product;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!checked_add_u64(minimum, UINT64_C(1), &minimum_plus_one) ||
        !checked_add_u64(maximum, UINT64_C(1), &maximum_plus_one) ||
        !checked_mul_u64(minimum, UINT64_C(2), &twice_minimum) ||
        !checked_add_u64(twice_minimum, UINT64_C(1), &factor3)) {
        return 0;
    }

    factor1 = minimum;
    factor2 = minimum_plus_one;

    if ((factor1 & UINT64_C(1)) == 0) {
        factor1 /= UINT64_C(2);
    } else {
        factor2 /= UINT64_C(2);
    }

    if (factor1 % UINT64_C(3) == 0) {
        factor1 /= UINT64_C(3);
    } else if (factor2 % UINT64_C(3) == 0) {
        factor2 /= UINT64_C(3);
    } else {
        factor3 /= UINT64_C(3);
    }

    if (!checked_mul_u64(factor1, factor2, &product) ||
        !checked_mul_u64(product, factor3, &sum)) {
        return 0;
    }

    factor1 = minimum;
    factor2 = minimum_plus_one;

    if ((factor1 & UINT64_C(1)) == 0) {
        factor1 /= UINT64_C(2);
    } else {
        factor2 /= UINT64_C(2);
    }

    if (!checked_mul_u64(factor1, factor2, &product) ||
        !checked_mul_u64(product, maximum_plus_one, &product) ||
        product < sum) {
        return 0;
    }

    *result = product - sum;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= size) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            }
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t result = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (!isdigit(*p)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        ++p;
    } while (isdigit(*p));

    *cursor = (const char *)p;
    *value = result;
    return 1;
}

static int read_input(uint64_t *width, uint64_t *height)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *cursor;

    if (width == NULL || height == NULL ||
        !read_line(buffer, sizeof buffer)) {
        return 0;
    }

    cursor = buffer;

    if (!parse_u64(&cursor, width) ||
        !parse_u64(&cursor, height)) {
        return 0;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_input(&width, &height)) {
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