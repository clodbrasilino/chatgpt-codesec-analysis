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

static int read_token(char **token)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 32;
    int c;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }

    if (c == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return 0;
    }

    *value = (size_t)parsed;
    free(token);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
    return 1;
}

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int find_similar_occurrences(int64_t *records,
                                    size_t length,
                                    RecordCount **results,
                                    size_t *result_count)
{
    RecordCount *counts = NULL;
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

    qsort(records, length, sizeof(*records), compare_int64);

    for (i = 0; i < length;) {
        size_t j = i + 1;

        while (j < length && records[j] == records[i]) {
            ++j;
        }

        if (j - i > 1) {
            ++unique_count;
        }

        i = j;
    }

    if (unique_count == 0) {
        return 0;
    }

    if (unique_count > SIZE_MAX / sizeof(*counts)) {
        return -1;
    }

    counts = malloc(unique_count * sizeof(*counts));
    if (counts == NULL) {
        return -1;
    }

    for (i = 0; i < length;) {
        size_t j = i + 1;

        while (j < length && records[j] == records[i]) {
            ++j;
        }

        if (j - i > 1) {
            counts[matched_count].value = records[i];
            counts[matched_count].count = j - i;
            ++matched_count;
        }

        i = j;
    }

    *results = counts;
    *result_count = matched_count;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t total_records = 0;
    size_t capacity = 0;
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

        if (new_total > capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity;
            int64_t *temporary;

            while (new_capacity < new_total) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = new_total;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*records)) {
                new_capacity = new_total;
            }

            temporary = realloc(records,
                                new_capacity * sizeof(*records));
            if (temporary == NULL) {
                free(records);
                return EXIT_FAILURE;
            }

            records = temporary;
            capacity = new_capacity;
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

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}