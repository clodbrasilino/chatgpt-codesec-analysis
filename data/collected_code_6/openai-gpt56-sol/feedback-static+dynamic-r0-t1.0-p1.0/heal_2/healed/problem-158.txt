#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_int64(int64_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    const intmax_t parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX ||
        end == buffer) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    const uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed == 0 ||
        parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int find_operations(int64_t *values, size_t count,
                           uint64_t *operations)
{
    if (values == NULL || operations == NULL || count == 0) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_int64);

    const int64_t median = values[count / 2];
    uint64_t total = 0;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference;

        if (values[i] >= median) {
            difference = (uint64_t)values[i] - (uint64_t)median;
        } else {
            difference = (uint64_t)median - (uint64_t)values[i];
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
    size_t count;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        perror("malloc");
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

    if (printf("%" PRIu64 "\n", operations) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}