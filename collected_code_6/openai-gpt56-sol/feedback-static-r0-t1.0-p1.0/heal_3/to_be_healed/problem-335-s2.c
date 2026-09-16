#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_progression_sum(int64_t first, int64_t difference,
                                      uint64_t terms, int64_t *sum)
{
    const __int128 n = (__int128)terms;
    const __int128 result =
        n * (2 * (__int128)first + (n - 1) * (__int128)difference) / 2;

    if (sum == NULL || result < INT64_MIN || result > INT64_MAX) {
        return -1;
    }

    *sum = (int64_t)result;
    return 0;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int64_t first;
    int64_t difference;
    int64_t sum;
    uint64_t terms;

    if (argc != 4) {
        fprintf(stderr,
                "Usage: %s <first-term> <common-difference> <term-count>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_int64(argv[1], &first) != 0 ||
        parse_int64(argv[2], &difference) != 0 ||
        parse_uint64(argv[3], &terms) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (arithmetic_progression_sum(first, difference, terms, &sum) != 0) {
        fputs("The sum is outside the int64_t range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}