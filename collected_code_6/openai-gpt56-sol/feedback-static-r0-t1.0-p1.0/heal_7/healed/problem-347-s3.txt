#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

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

static int read_nonspace(int *character)
{
    int ch;

    if (character == NULL) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    *character = ch;
    return 1;
}

static int read_u64(uint64_t *value)
{
    uint64_t result = 0;
    int ch;

    if (value == NULL || !read_nonspace(&ch) ||
        !isdigit((unsigned char)ch)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        ch = getchar();
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (ch != EOF && ungetc(ch, stdin) == EOF) {
        return 0;
    }

    *value = result;
    return 1;
}

static int read_input(uint64_t *width, uint64_t *height)
{
    int ch;

    if (width == NULL || height == NULL ||
        !read_u64(width) || !read_u64(height)) {
        return 0;
    }

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
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