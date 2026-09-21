#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && b < INT64_MAX / a)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int minimum_tuple_product(const Tuple *tuples, size_t count,
                                 int64_t *minimum)
{
    int64_t product;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    if (!multiply_checked(tuples[0].first, tuples[0].second, minimum)) {
        return 0;
    }

    for (size_t i = 1; i < count; ++i) {
        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return 0;
        }

        if (product < *minimum) {
            *minimum = product;
        }
    }

    return 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed == 0 ||
        parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_tuple(Tuple *tuple)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *first_end;
    char *second_start;
    char *second_end;
    intmax_t first;
    intmax_t second;

    if (tuple == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    first_end = NULL;
    first = strtoimax(buffer, &first_end, 10);

    if (errno == ERANGE || first_end == buffer ||
        first < INT64_MIN || first > INT64_MAX) {
        return 0;
    }

    second_start = first_end;
    while (*second_start == ' ' || *second_start == '\t') {
        ++second_start;
    }

    errno = 0;
    second_end = NULL;
    second = strtoimax(second_start, &second_end, 10);

    if (errno == ERANGE || second_end == second_start ||
        second < INT64_MIN || second > INT64_MAX) {
        return 0;
    }

    while (*second_end == ' ' || *second_end == '\t' ||
           *second_end == '\r' || *second_end == '\n') {
        ++second_end;
    }

    if (*second_end != '\0') {
        return 0;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t minimum;
    int status = EXIT_FAILURE;

    if (!read_size(&count) || count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_tuple(&tuples[i])) {
            fputs("Invalid tuple input\n", stderr);
            goto cleanup;
        }
    }

    if (!minimum_tuple_product(tuples, count, &minimum)) {
        fputs("Unable to calculate product safely\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}