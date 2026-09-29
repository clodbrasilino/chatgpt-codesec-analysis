#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t digit_distance(int64_t first, int64_t second)
{
    uint64_t left = magnitude(first);
    uint64_t right = magnitude(second);
    uint64_t distance = 0;

    do {
        uint64_t left_digit = left % UINT64_C(10);
        uint64_t right_digit = right % UINT64_C(10);

        distance += left_digit >= right_digit
                        ? left_digit - right_digit
                        : right_digit - left_digit;

        left /= UINT64_C(10);
        right /= UINT64_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    int64_t first;
    int64_t second;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}