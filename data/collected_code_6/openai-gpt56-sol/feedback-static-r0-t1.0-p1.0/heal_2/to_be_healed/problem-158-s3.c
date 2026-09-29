#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int find_operations(int64_t *values, size_t count,
                           uint64_t *operations)
{
    if (values == NULL || operations == NULL || count == 0) {
        return -1;
    }

    qsort(values, count, sizeof *values, compare_int64);

    const int64_t target = values[count / 2];
    uint64_t total = 0;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference;

        if (values[i] >= target) {
            difference = (uint64_t)values[i] - (uint64_t)target;
        } else {
            difference = (uint64_t)target - (uint64_t)values[i];
        }

        if (difference > UINT64_MAX - total) {
            return -1;
        }

        total += difference;
    }

    *operations = total;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed_count;
    size_t count;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed_count = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || *start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed_count == 0 ||
        parsed_count > SIZE_MAX ||
        parsed_count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)parsed_count;

    int64_t *values = malloc(count * sizeof *values);
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t operations;
    if (find_operations(values, count, &operations) != 0) {
        fputs("Unable to calculate operations\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", operations);
    free(values);

    return EXIT_SUCCESS;
}