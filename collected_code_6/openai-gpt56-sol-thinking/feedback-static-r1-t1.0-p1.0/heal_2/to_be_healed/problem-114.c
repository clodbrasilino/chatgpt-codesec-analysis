#include <ctype.h>
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

typedef struct {
    int first;
    int second;
    size_t index;
} TupleIndex;

static int read_magnitude(FILE *stream,
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

    if (stream == NULL || value == NULL || is_negative == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            valid = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            have_digit = 1;

            if (!overflow) {
                if (result > limit / 10 ||
                    (result == limit / 10 && digit > limit % 10)) {
                    overflow = 1;
                } else {
                    result = result * 10 + digit;
                }
            }
        } else {
            valid = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    if (!valid || !have_digit || overflow) {
        return -1;
    }

    *value = result;
    *is_negative = negative;
    return 0;
}

static int read_size(FILE *stream, size_t *value)
{
    uintmax_t parsed;
    int negative;

    if (value == NULL) {
        return -1;
    }

    if (read_magnitude(stream,
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

static int read_int(FILE *stream, int *value)
{
    uintmax_t parsed;
    uintmax_t negative_limit;
    int negative;

    if (value == NULL) {
        return -1;
    }

    negative_limit = (uintmax_t)(-(INT_MIN + 1)) + 1;

    if (read_magnitude(stream,
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