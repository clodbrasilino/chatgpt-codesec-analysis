#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end;
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
    char *end;
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

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    uint64_t ua = (uint64_t)a;
    uint64_t ub = (uint64_t)b;

    return a >= b ? ua - ub : ub - ua;
}

static int find_minimum_difference(const Tuple *tuples, size_t count,
                                   uint64_t *minimum)
{
    uint64_t current_minimum;
    size_t i;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    current_minimum =
        absolute_difference(tuples[0].first, tuples[0].second);

    for (i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < current_minimum) {
            current_minimum = difference;
        }
    }

    *minimum = current_minimum;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    uint64_t minimum;
    size_t i;

    if (!read_size(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int64(&tuples[i].first) ||
            !read_int64(&tuples[i].second)) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_difference(tuples, count, &minimum)) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}