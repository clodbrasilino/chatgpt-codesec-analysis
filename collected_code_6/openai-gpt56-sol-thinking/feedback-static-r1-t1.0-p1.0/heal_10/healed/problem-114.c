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
} TupleIndex;

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int error;
    int end_of_file;
} InputReader;

static int input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return -1;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->error = 0;
    reader->end_of_file = 0;

    return 0;
}

static int input_reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL ||
        reader->error || reader->end_of_file) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->position = 0;
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->error = 1;
            } else {
                reader->end_of_file = 1;
            }

            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int read_magnitude(InputReader *reader,
                          uintmax_t positive_limit,
                          uintmax_t negative_limit,
                          int allow_negative,
                          uintmax_t *value,
                          int *is_negative)
{
    int ch;
    int negative = 0;
    int valid = 1;
    int have_digit = 0;
    int overflow = 0;
    uintmax_t result = 0;
    uintmax_t limit;

    if (reader == NULL || value == NULL || is_negative == NULL) {
        return -1;
    }

    do {
        ch = input_reader_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            valid = 0;
        }

        ch = input_reader_get(reader);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            have_digit = 1;

            if (!overflow) {
                if (result > limit / UINTMAX_C(10) ||
                    (result == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    overflow = 1;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        ch = input_reader_get(reader);
    }

    if (reader->error || !valid || !have_digit || overflow) {
        return -1;
    }

    *value = result;
    *is_negative = negative;

    return 0;
}

static int read_size(InputReader *reader, size_t *value)
{
    uintmax_t parsed;
    int negative;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    if (read_magnitude(reader,
                       (uintmax_t)SIZE_MAX,
                       (uintmax_t)SIZE_MAX,
                       0,
                       &parsed,
                       &negative) != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int(InputReader *reader, int *value)
{
    uintmax_t parsed;
    uintmax_t negative_limit;
    int negative;

    if (reader == NULL || value == NULL) {
        return -1;
    }

    negative_limit = (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);

    if (read_magnitude(reader,
                       (uintmax_t)INT_MAX,
                       negative_limit,
                       1,
                       &parsed,
                       &negative) != 0) {
        return -1;
    }

    if (!negative) {
        *value = (int)parsed;
    } else if (parsed == negative_limit) {
        *value = INT_MIN;
    } else {
        *value = -(int)parsed;
    }

    return 0;
}

static int compare_tuple_indices(const void *left, const void *right)
{
    const TupleIndex *a = left;
    const TupleIndex *b = right;

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
    TupleIndex *indices;
    size_t i;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*indices)) {
        return -1;
    }

    indices = malloc(count * sizeof(*indices));
    if (indices == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        indices[i].first = tuples[i].first;
        indices[i].second = tuples[i].second;
        indices[i].index = i;
    }

    qsort(indices, count, sizeof(*indices), compare_tuple_indices);

    i = 0;

    while (i < count) {
        size_t j = i + 1;
        size_t frequency;
        size_t k;

        while (j < count &&
               indices[j].first == indices[i].first &&
               indices[j].second == indices[i].second) {
            ++j;
        }

        frequency = j - i;

        for (k = i; k < j; ++k) {
            tuples[indices[k].index].frequency = frequency;
        }

        i = j;
    }

    free(indices);
    return 0;
}

int main(void)
{
    InputReader reader;
    Tuple *tuples = NULL;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    if (input_reader_init(&reader, stdin) != 0) {
        fputs("Unable to initialize input reader.\n", stderr);
        return EXIT_FAILURE;
    }

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
            goto cleanup;
        }

        tuples[i].frequency = 0;
    }

    if (assign_tuple_frequencies(tuples, count) != 0) {
        fputs("Unable to assign tuple frequencies.\n", stderr);
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (printf("(%d, %d): %zu\n",
                   tuples[i].first,
                   tuples[i].second,
                   tuples[i].frequency) < 0) {
            fputs("Unable to write output.\n", stderr);
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        fputs("Unable to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}