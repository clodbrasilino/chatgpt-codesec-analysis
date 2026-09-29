#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    return value < 0
        ? UINT64_C(0) - (uint64_t)value
        : (uint64_t)value;
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        uint64_t left_digit = left % UINT64_C(10);
        uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit > right_digit
            ? left_digit - right_digit
            : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[64];
    char *end;
    intmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%63s", token) != 1) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    int64_t first;
    int64_t second;
    int ch;

    if (!read_int64(&first) || !read_int64(&second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}