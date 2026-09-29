#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

static int read_token(FILE *stream, char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    int too_long = 0;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stream) ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = 1;
        }
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    if (too_long) {
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(FILE *stream, size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(stream, token, sizeof(token));
    if (status != 1 || token[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int(FILE *stream, int *value)
{
    char token[128];
    char *end;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(stream, token, sizeof(token));
    if (status != 1) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

static int assign_tuple_frequencies(Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        tuples[i].frequency = 0;

        for (j = 0; j < count; ++j) {
            if (tuples[i].first == tuples[j].first &&
                tuples[i].second == tuples[j].second) {
                ++tuples[i].frequency;
            }
        }
    }

    return 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t count;
    size_t i;

    if (read_size(stdin, &count) != 0) {
        fputs("Invalid tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple list is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Unable to allocate tuple list.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; ++i) {
        if (read_int(stdin, &tuples[i].first) != 0 ||
            read_int(stdin, &tuples[i].second) != 0) {
            fputs("Invalid tuple data.\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
        tuples[i].frequency = 0;
    }

    if (assign_tuple_frequencies(tuples, count) != 0) {
        fputs("Unable to assign tuple frequencies.\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("(%d, %d): %zu\n",
                   tuples[i].first,
                   tuples[i].second,
                   tuples[i].frequency) < 0) {
            fputs("Unable to write output.\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    free(tuples);
    return EXIT_SUCCESS;
}