#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t value;
    size_t count;
} RecordCount;

static int read_token(char *buffer, size_t capacity)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length + 1 >= capacity) {
            do {
                c = getchar();
            } while (c != EOF && !isspace((unsigned char)c));
            return 0;
        }

        buffer[length++] = (char)c;
        c = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) || token[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char token[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int find_similar_occurrences(const int64_t *records, size_t length,
                                    RecordCount **results,
                                    size_t *result_count)
{
    int64_t *sorted;
    RecordCount *counts;
    size_t unique_count = 0;
    size_t matched_count = 0;
    size_t i;

    if (results == NULL || result_count == NULL ||
        (records == NULL && length != 0)) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        sorted[i] = records[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_int64);

    for (i = 0; i < length;) {
        size_t j = i + 1;

        while (j < length && sorted[j] == sorted[i]) {
            ++j;
        }

        if (j - i > 1) {
            ++unique_count;
        }

        i = j;
    }

    if (unique_count == 0) {
        free(sorted);
        return 0;
    }

    if (unique_count > SIZE_MAX / sizeof(*counts)) {
        free(sorted);
        return -1;
    }

    counts = malloc(unique_count * sizeof(*counts));
    if (counts == NULL) {
        free(sorted);
        return -1;
    }

    for (i = 0; i < length;) {
        size_t j = i + 1;

        while (j < length && sorted[j] == sorted[i]) {
            ++j;
        }

        if (j - i > 1) {
            counts[matched_count].value = sorted[i];
            counts[matched_count].count = j - i;
            ++matched_count;
        }

        i = j;
    }

    free(sorted);
    *results = counts;
    *result_count = matched_count;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t total_records = 0;
    int64_t *records = NULL;
    RecordCount *results = NULL;
    size_t result_count = 0;
    size_t i;

    if (!read_size(&tuple_count)) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        size_t tuple_size;
        size_t new_total;
        size_t j;
        int64_t *resized;

        if (!read_size(&tuple_size)) {
            free(records);
            return EXIT_FAILURE;
        }

        if (tuple_size > SIZE_MAX - total_records) {
            free(records);
            return EXIT_FAILURE;
        }

        new_total = total_records + tuple_size;

        if (new_total > SIZE_MAX / sizeof(*records)) {
            free(records);
            return EXIT_FAILURE;
        }

        if (new_total != total_records) {
            resized = realloc(records, new_total * sizeof(*records));
            if (resized == NULL) {
                free(records);
                return EXIT_FAILURE;
            }
            records = resized;
        }

        for (j = total_records; j < new_total; ++j) {
            if (!read_int64(&records[j])) {
                free(records);
                return EXIT_FAILURE;
            }
        }

        total_records = new_total;
    }

    if (find_similar_occurrences(records, total_records,
                                 &results, &result_count) != 0) {
        free(records);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%" PRId64 " %zu\n",
                   results[i].value, results[i].count) < 0) {
            free(results);
            free(records);
            return EXIT_FAILURE;
        }
    }

    free(results);
    free(records);
    return EXIT_SUCCESS;
}