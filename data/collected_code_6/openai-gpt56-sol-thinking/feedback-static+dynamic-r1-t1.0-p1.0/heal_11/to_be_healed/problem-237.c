#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef enum {
    CHECK_ERROR = -1,
    CHECK_NOT_EQUAL = 0,
    CHECK_EQUAL = 1
} CheckResult;

typedef struct {
    FILE *stream;
    int at_end;
    int failed;
} InputReader;

static int input_get(InputReader *reader)
{
    int ch;

    if (reader == NULL || reader->stream == NULL ||
        reader->failed || reader->at_end) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(reader->stream);

    if (ch == EOF) {
        if (ferror(reader->stream)) {
            reader->failed = 1;
        } else {
            reader->at_end = 1;
        }
    }

    return ch;
}

static int read_decimal_token(InputReader *reader,
                              uintmax_t positive_limit,
                              uintmax_t negative_limit,
                              int allow_negative,
                              uintmax_t *magnitude,
                              int *is_negative)
{
    uintmax_t value = 0;
    uintmax_t limit;
    int ch;
    int negative = 0;
    int has_digit = 0;
    int valid = 1;
    int overflow = 0;

    if (reader == NULL || reader->stream == NULL ||
        magnitude == NULL || is_negative == NULL) {
        return 0;
    }

    do {
        ch = input_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            valid = 0;
        }

        ch = input_get(reader);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = 1;

            if (!overflow) {
                if (value > limit / UINTMAX_C(10) ||
                    (value == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    overflow = 1;
                } else {
                    value = value * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        ch = input_get(reader);
    }

    if (reader->failed || !has_digit || !valid || overflow) {
        return 0;
    }

    *magnitude = value;
    *is_negative = negative;
    return 1;
}

static int read_size_value(InputReader *reader, size_t *value)
{
    uintmax_t magnitude;
    int negative;

    if (reader == NULL || value == NULL) {
        return 0;
    }

    if (!read_decimal_token(reader,
                            (uintmax_t)SIZE_MAX,
                            UINTMAX_C(0),
                            0,
                            &magnitude,
                            &negative)) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_int64_value(InputReader *reader, int64_t *value)
{
    const uintmax_t positive_limit = (uintmax_t)INT64_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);
    uintmax_t magnitude;
    int negative;

    if (reader == NULL || value == NULL) {
        return 0;
    }

    if (!read_decimal_token(reader,
                            positive_limit,
                            negative_limit,
                            1,
                            &magnitude,
                            &negative)) {
        return 0;
    }

    if (negative) {
        if (magnitude == negative_limit) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return 1;
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

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

static int tuples_are_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first &&
           left->second == right->second;
}

static CheckResult records_have_equal_occurrences(Tuple *tuples,
                                                   size_t count)
{
    size_t index = 0;
    size_t expected_frequency = 0;

    if (count == 0) {
        return CHECK_EQUAL;
    }

    if (tuples == NULL || count > SIZE_MAX / sizeof(*tuples)) {
        return CHECK_ERROR;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    while (index < count) {
        size_t end = index + 1;
        size_t frequency;

        while (end < count &&
               tuples_are_equal(&tuples[index], &tuples[end])) {
            ++end;
        }

        frequency = end - index;

        if (expected_frequency == 0) {
            expected_frequency = frequency;
        } else if (frequency != expected_frequency) {
            return CHECK_NOT_EQUAL;
        }

        index = end;
    }

    return CHECK_EQUAL;
}

int main(void)
{
    InputReader reader = {
        .stream = stdin,
        .at_end = 0,
        .failed = 0
    };
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;

    if (!read_size_value(&reader, &count)) {
        fputs("Failed to read the tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));

        if (tuples == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < count; ++index) {
        if (!read_int64_value(&reader, &tuples[index].first) ||
            !read_int64_value(&reader, &tuples[index].second)) {
            fprintf(stderr, "Failed to read tuple %zu.\n", index + 1);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = records_have_equal_occurrences(tuples, count);
    free(tuples);

    if (result == CHECK_ERROR) {
        fputs("Unable to check record occurrences.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == CHECK_EQUAL ? "YES" : "NO");
    return EXIT_SUCCESS;
}