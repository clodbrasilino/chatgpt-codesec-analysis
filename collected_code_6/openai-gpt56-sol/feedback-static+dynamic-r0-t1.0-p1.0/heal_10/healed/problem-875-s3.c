#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int find_minimum_difference(const Tuple *tuples, size_t count,
                                   uint64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0U) {
        return -1;
    }

    *minimum = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1U; i < count; ++i) {
        uint64_t current =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (current < *minimum) {
            *minimum = current;
        }
    }

    return 0;
}

static int read_token(char **token)
{
    enum {
        MAX_TOKEN_LENGTH = 128
    };

    char *buffer;
    size_t length = 0U;
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
    } while (isspace((unsigned char)ch) != 0);

    buffer = malloc((size_t)MAX_TOKEN_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && isspace((unsigned char)ch) == 0) {
        if (length >= (size_t)MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && isspace((unsigned char)ch) == 0);

            free(buffer);
            return -1;
        }

        buffer[length] = (char)ch;
        ++length;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin) != 0) {
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
    int status = -1;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(token);
    return status;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(token);
    return status;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t minimum;
    int result = EXIT_FAILURE;

    if (read_size(&count) != 0 || count == 0U ||
        count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_int64(&tuples[i].first) != 0 ||
            read_int64(&tuples[i].second) != 0) {
            goto cleanup;
        }
    }

    if (find_minimum_difference(tuples, count, &minimum) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return result;
}