#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int64_t value;
    size_t count;
} RecordCount;

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    enum { MAX_TOKEN_LENGTH = 1024 };
    char *buffer;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc((size_t)MAX_TOKEN_LENGTH + 1);
    if (buffer == NULL) {
        return -1;
    }

    do {
        if (length == (size_t)MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            free(buffer);
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
    return 0;
}

static int find_similar_occurrences(const int64_t *records,
                                    size_t length,
                                    RecordCount **results,
                                    size_t *result_count)
{
    int64_t *sorted = NULL;
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
    size_t capacity = 0;
    int64_t *records = NULL;
    RecordCount *results = NULL;
    size_t result_count = 0;
    size_t i;

    if (read_size(&tuple_count) != 0) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        size_t tuple_size;
        size_t new_total;
        size_t j;

        if (read_size(&tuple_size) != 0 ||
            tuple_size > SIZE_MAX - total_records) {
            free(records);
            return EXIT_FAILURE;
        }

        new_total = total_records + tuple_size;

        if (new_total > SIZE_MAX / sizeof(*records)) {
            free(records);
            return EXIT_FAILURE;
        }

        if (new_total > capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity;
            int64_t *resized;

            while (new_capacity < new_total) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = new_total;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity < new_total ||
                new_capacity > SIZE_MAX / sizeof(*records)) {
                free(records);
                return EXIT_FAILURE;
            }

            resized = realloc(records, new_capacity * sizeof(*records));
            if (resized == NULL) {
                free(records);
                return EXIT_FAILURE;
            }

            records = resized;
            capacity = new_capacity;
        }

        for (j = total_records; j < new_total; ++j) {
            if (read_int64(&records[j]) != 0) {
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