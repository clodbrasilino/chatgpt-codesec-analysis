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
} Input;

static int input_get(Input *input, int *character)
{
    int result;

    if (input == NULL || character == NULL || input->stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    result = fgetc(input->stream);

    if (result == EOF) {
        return ferror(input->stream) ? -1 : 0;
    }

    *character = result;
    return 1;
}

static int read_first_nonspace(Input *input, int *character)
{
    int status;

    if (input == NULL || character == NULL) {
        return -1;
    }

    while ((status = input_get(input, character)) == 1) {
        if (!isspace((unsigned char)*character)) {
            return 1;
        }
    }

    return status;
}

static int read_size_value(Input *input, size_t *value)
{
    size_t parsed = 0;
    int character;
    int status;
    int valid = 1;

    if (input == NULL || value == NULL) {
        return 0;
    }

    status = read_first_nonspace(input, &character);
    if (status != 1) {
        return 0;
    }

    do {
        if (character >= '0' && character <= '9') {
            size_t digit = (size_t)(character - '0');

            if (valid) {
                if (parsed > (SIZE_MAX - digit) / 10) {
                    valid = 0;
                } else {
                    parsed = parsed * 10 + digit;
                }
            }
        } else {
            valid = 0;
        }

        status = input_get(input, &character);
    } while (status == 1 && !isspace((unsigned char)character));

    if (status < 0 || !valid) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_int64_value(Input *input, int64_t *value)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    int character;
    int status;
    int negative = 0;
    int first = 1;
    int has_digit = 0;
    int valid = 1;

    if (input == NULL || value == NULL) {
        return 0;
    }

    status = read_first_nonspace(input, &character);
    if (status != 1) {
        return 0;
    }

    do {
        if (first && (character == '+' || character == '-')) {
            negative = character == '-';
        } else if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = 1;
            limit = (uintmax_t)INT64_MAX +
                    (negative ? UINTMAX_C(1) : UINTMAX_C(0));

            if (valid) {
                if (magnitude > (limit - digit) / UINTMAX_C(10)) {
                    valid = 0;
                } else {
                    magnitude = magnitude * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        first = 0;
        status = input_get(input, &character);
    } while (status == 1 && !isspace((unsigned char)character));

    if (status < 0 || !valid || !has_digit) {
        return 0;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
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

static int tuples_are_equal(const Tuple *a, const Tuple *b)
{
    return a->first == b->first && a->second == b->second;
}

static CheckResult records_have_equal_occurrences(Tuple *tuples, size_t count)
{
    size_t index = 0;
    size_t expected_frequency = 0;

    if (count == 0) {
        return CHECK_EQUAL;
    }

    if (tuples == NULL) {
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
    Input input = { stdin };
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;

    if (!read_size_value(&input, &count)) {
        fprintf(stderr, "Failed to read the tuple count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large.\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < count; ++index) {
        if (!read_int64_value(&input, &tuples[index].first) ||
            !read_int64_value(&input, &tuples[index].second)) {
            fprintf(stderr, "Failed to read tuple %zu.\n", index + 1);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = records_have_equal_occurrences(tuples, count);
    free(tuples);

    if (result == CHECK_ERROR) {
        fprintf(stderr, "Unable to check record occurrences.\n");
        return EXIT_FAILURE;
    }

    puts(result == CHECK_EQUAL ? "YES" : "NO");
    return EXIT_SUCCESS;
}