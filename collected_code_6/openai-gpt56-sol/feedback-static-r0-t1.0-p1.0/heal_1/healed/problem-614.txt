#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    end = buffer;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_tuple(Tuple *tuple)
{
    char buffer[256];
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (tuple == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    cursor = buffer;
    errno = 0;
    first = strtoimax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor ||
        first < INT64_MIN || first > INT64_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor ||
        second < INT64_MIN || second > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    return 1;
}

static int add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int cumulative_sum(const Tuple *tuples, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!add_int64(sum, tuples[i].first, &sum) ||
            !add_int64(sum, tuples[i].second, &sum)) {
            return 0;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t sum;

    if (!read_size(&count)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_tuple(&tuples[i])) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!cumulative_sum(tuples, count, &sum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}