#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>

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

static int discard_to_end_of_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return !ferror(stdin);
}

static int read_input(uint64_t *width, uint64_t *height)
{
    char buffer[256];
    char extra;
    uintmax_t parsed_width;
    uintmax_t parsed_height;
    int matched;
    int ch;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        if (!discard_to_end_of_line()) {
            return 0;
        }
        return 0;
    }

    if (ferror(stdin)) {
        return 0;
    }

    matched = sscanf(buffer, " %" SCNuMAX " %" SCNuMAX " %c",
                     &parsed_width, &parsed_height, &extra);

    if (matched != 2 ||
        parsed_width > UINT64_MAX ||
        parsed_height > UINT64_MAX) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    if (ferror(stdin)) {
        return 0;
    }

    *width = (uint64_t)parsed_width;
    *height = (uint64_t)parsed_height;
    return 1;
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