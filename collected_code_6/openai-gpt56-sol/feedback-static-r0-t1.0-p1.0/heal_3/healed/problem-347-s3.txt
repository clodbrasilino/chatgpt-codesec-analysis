#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t factor1;
    uint64_t factor2;
    uint64_t factor3;
    uint64_t sum;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    factor1 = minimum;
    factor2 = minimum + 1;
    factor3 = 2 * minimum + 1;

    if (minimum == UINT64_MAX || minimum > (UINT64_MAX - 1) / 2) {
        return 0;
    }

    if ((factor1 & 1U) == 0) {
        factor1 /= 2;
    } else {
        factor2 /= 2;
    }

    if (factor1 % 3 == 0) {
        factor1 /= 3;
    } else if (factor2 % 3 == 0) {
        factor2 /= 3;
    } else {
        factor3 /= 3;
    }

    if (factor1 != 0 && factor2 > UINT64_MAX / factor1) {
        return 0;
    }

    sum = factor1 * factor2;

    if (factor3 != 0 && sum > UINT64_MAX / factor3) {
        return 0;
    }

    sum *= factor3;

    if (maximum == UINT64_MAX) {
        return 0;
    }

    factor1 = minimum;
    factor2 = minimum + 1;

    if ((factor1 & 1U) == 0) {
        factor1 /= 2;
    } else {
        factor2 /= 2;
    }

    if (factor1 != 0 && factor2 > UINT64_MAX / factor1) {
        return 0;
    }

    factor1 *= factor2;

    if (factor1 != 0 && maximum + 1 > UINT64_MAX / factor1) {
        return 0;
    }

    factor1 *= maximum + 1;

    if (factor1 < sum) {
        return 0;
    }

    *result = factor1 - sum;
    return 1;
}

static int read_uint64(FILE *stream, uint64_t *value)
{
    int ch;
    int digit_seen = 0;
    uint64_t parsed = 0;

    if (stream == NULL || value == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF || ch == '+' || ch == '-' || !isdigit((unsigned char)ch)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        digit_seen = 1;

        if (parsed > (UINT64_MAX - digit) / 10) {
            return 0;
        }

        parsed = parsed * 10 + digit;
        ch = fgetc(stream);
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (ch != EOF && ungetc(ch, stream) == EOF) {
        return 0;
    }

    if (!digit_seen) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int only_whitespace_remains(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stream);
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    errno = 0;

    if (!read_uint64(stdin, &width) ||
        !read_uint64(stdin, &height) ||
        !only_whitespace_remains(stdin)) {
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