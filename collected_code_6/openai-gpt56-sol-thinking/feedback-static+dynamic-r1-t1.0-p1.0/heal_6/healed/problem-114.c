#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

typedef struct {
    int first;
    int second;
    size_t index;
} TupleKey;

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
} InputReader;

static int reader_get(InputReader *reader, int *character)
{
    if (reader == NULL || reader->stream == NULL || character == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *character = (int)reader->buffer[reader->position++];
    return 1;
}

static int read_nonspace(InputReader *reader, int *character)
{
    int status;

    if (reader == NULL || character == NULL) {
        return -1;
    }

    do {
        status = reader_get(reader, character);
        if (status != 1) {
            return status;
        }
    } while (isspace((unsigned char)*character));

    return 1;
}

static int read_size(InputReader *reader, size_t *value)
{
    size_t result = 0;
    int character;
    int status;
    int saw_digit = 0;
    int invalid = 0;
    int overflow = 0;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    status = read_nonspace(reader, &character);
    if (status != 1) {
        return -1;
    }

    if (character == '+' || character == '-') {
        if (character == '-') {
            invalid = 1;
        }

        status = reader_get(reader, &character);
    }

    while (status == 1 && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            size_t digit = (size_t)(character - '0');

            saw_digit = 1;

            if (!overflow) {
                if (result > SIZE_MAX / 10U ||
                    (result == SIZE_MAX / 10U &&
                     digit > SIZE_MAX % 10U)) {
                    overflow = 1;
                } else {
                    result = result * 10U + digit;
                }
            }
        } else {
            invalid = 1;
        }

        status = reader_get(reader, &character);
    }

    if (status < 0 || !saw_digit || invalid || overflow) {
        return -1;
    }

    *value = result;
    return 0;
}

static int read_int(InputReader *reader, int *value)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    uintmax_t minimum_magnitude;
    int character;
    int status;
    int negative = 0;
    int saw_digit = 0;
    int invalid = 0;
    int overflow = 0;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    status = read_nonspace(reader, &character);
    if (status != 1) {
        return -1;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        status = reader_get(reader, &character);
    }

    minimum_magnitude = (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);
    limit = negative ? minimum_magnitude : (uintmax_t)INT_MAX;

    while (status == 1 && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            saw_digit = 1;

            if (!overflow) {
                if (magnitude > limit / UINTMAX_C(10) ||
                    (magnitude == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    overflow = 1;
                } else {
                    magnitude = magnitude * UINTMAX_C(10) + digit;
                }
            }
        } else {
            invalid = 1;
        }

        status = reader_get(reader, &character);
    }

    if (status < 0 || !saw_digit || invalid || overflow) {
        return -1;
    }

    if (negative) {
        if (magnitude == minimum_magnitude) {
            *value = INT_MIN;
        } else {
            *value = -(int)magnitude;
        }
    } else {
        *value = (int)magnitude;
    }

    return 0;
}

static int compare_tuple_keys(const void *left, const void *right)
{
    const TupleKey *a = left;
    const TupleKey *b = right;

    if (a->first < b->first) {
        return -1;
    }

    if (a->first > b->first) {
        return 1;
    }

    if (a->second < b->second) {
        return -1;
    }

    if (a->second > b->second) {
        return 1;
    }

    return 0;
}

static int assign_tuple_frequencies(Tuple *tuples, size_t count)
{
    TupleKey *keys;
    size_t i;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*keys)) {
        return -1;
    }

    keys = malloc(count * sizeof(*keys));
    if (keys == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        keys[i].first = tuples[i].first;
        keys[i].second = tuples[i].second;
        keys[i].index = i;
    }

    qsort(keys, count, sizeof(*keys), compare_tuple_keys);

    i = 0;
    while (i < count) {
        size_t end = i + 1;
        size_t frequency;
        size_t j;

        while (end < count &&
               keys[end].first == keys[i].first &&
               keys[end].second == keys[i].second) {
            ++end;
        }

        frequency = end - i;

        for (j = i; j < end; ++j) {
            tuples[keys[j].index].frequency = frequency;
        }

        i = end;
    }

    free(keys);
    return 0;
}

int main(void)
{
    InputReader reader = {
        .stream = stdin,
        .position = 0,
        .length = 0
    };
    Tuple *tuples = NULL;
    size_t count;
    size_t i;

    if (read_size(&reader, &count) != 0) {
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
        if (read_int(&reader, &tuples[i].first) != 0 ||
            read_int(&reader, &tuples[i].second) != 0) {
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

    if (fflush(stdout) == EOF) {
        fputs("Unable to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}