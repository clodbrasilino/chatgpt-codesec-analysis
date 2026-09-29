#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <inttypes.h>

static int arithmetic_progression_sum(int64_t first, int64_t difference,
                                      uint64_t terms, int64_t *sum)
{
    if (sum == NULL) {
        return -1;
    }

    if (terms == 0U) {
        *sum = 0;
        return 0;
    }

    if (terms - 1U > (uint64_t)INT64_MAX) {
        return -1;
    }

    const int64_t count_minus_one = (int64_t)(terms - 1U);
    int64_t last;

    if (__builtin_mul_overflow(count_minus_one, difference, &last) ||
        __builtin_add_overflow(first, last, &last)) {
        return -1;
    }

    int64_t pair_sum;
    if (__builtin_add_overflow(first, last, &pair_sum)) {
        return -1;
    }

    int64_t signed_terms;
    if (terms > (uint64_t)INT64_MAX) {
        return -1;
    }
    signed_terms = (int64_t)terms;

    int64_t factor_a = signed_terms;
    int64_t factor_b = pair_sum;

    if ((factor_a % 2) == 0) {
        factor_a /= 2;
    } else {
        factor_b /= 2;
    }

    if (__builtin_mul_overflow(factor_a, factor_b, sum)) {
        return -1;
    }

    return 0;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
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
    char *end = NULL;
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

int main(int argc, char *argv[])
{
    int64_t first;
    int64_t difference;
    uint64_t terms;
    int64_t sum;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first> <difference> <terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_int64(argv[1], &first) != 0 ||
        parse_int64(argv[2], &difference) != 0 ||
        parse_uint64(argv[3], &terms) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (arithmetic_progression_sum(first, difference, terms, &sum) != 0) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}