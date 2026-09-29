#include <ctype.h>
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
} TupleKey;

static int read_nonspace(FILE *stream, int *character)
{
    int ch;

    if (stream == NULL || character == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stream) ? -1 : 0;
    }

    *character = ch;
    return 1;
}

static int read_size(FILE *stream, size_t *value)
{
    size_t result = 0;
    int ch;
    int status;
    int saw_digit = 0;
    int invalid = 0;
    int overflow = 0;

    if (stream == NULL || value == NULL) {
        return -1;
    }

    status = read_nonspace(stream, &ch);
    if (status != 1) {
        return -1;
    }

    if (ch == '+' || ch == '-') {
        if (ch == '-') {
            invalid = 1;
        }
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            size_t digit = (size_t)(ch - '0');

            saw_digit = 1;
            if (!overflow) {
                if (result > (SIZE_MAX - digit) / 10) {
                    overflow = 1;
                } else {
                    result = result * 10 + digit;
                }
            }
        } else {
            invalid = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    if (!saw_digit || invalid || overflow) {
        return -1;
    }

    *value = result;
    return 0;
}

static int read_int(FILE *stream, int *value)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    int ch;
    int status;
    int negative = 0;
    int saw_digit = 0;
    int invalid = 0;
    int overflow = 0;

    if (stream == NULL || value == NULL) {
        return -1;
    }

    status = read_nonspace(stream, &ch);
    if (status != 1) {
        return -1;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    limit = negative
                ? (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1)
                : (uintmax_t)INT_MAX;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            saw_digit = 1;
            if (!overflow) {
                if (magnitude > (limit - digit) / UINTMAX_C(10)) {
                    overflow = 1;
                } else {
                    magnitude = magnitude * UINTMAX_C(10) + digit;
                }
            }
        } else {
            invalid = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    if (!saw_digit || invalid || overflow) {
        return -1;
    }

    if (negative) {
        uintmax_t minimum_magnitude =
            (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);

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