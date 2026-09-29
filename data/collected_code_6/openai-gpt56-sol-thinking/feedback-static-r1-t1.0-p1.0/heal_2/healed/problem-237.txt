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

static int read_first_nonspace(int *character)
{
    int current;

    if (character == NULL) {
        return -1;
    }

    while ((current = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)current)) {
            *character = current;
            return 1;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_size_value(size_t *value)
{
    size_t parsed = 0;
    int character;
    int status;
    int valid = 1;

    if (value == NULL) {
        return 0;
    }

    status = read_first_nonspace(&character);
    if (status != 1) {
        return 0;
    }

    do {
        if (isdigit((unsigned char)character)) {
            size_t digit = (size_t)(character - '0');

            if (parsed > (SIZE_MAX - digit) / 10) {
                valid = 0;
            } else if (valid) {
                parsed = parsed * 10 + digit;
            }
        } else {
            valid = 0;
        }

        character = fgetc(stdin);
    } while (character != EOF && !isspace((unsigned char)character));

    if (character == EOF && ferror(stdin)) {
        return 0;
    }

    if (!valid) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    int character;
    int status;
    int negative = 0;
    int first = 1;
    int has_digit = 0;
    int valid = 1;

    if (value == NULL) {
        return 0;
    }

    status = read_first_nonspace(&character);
    if (status != 1) {
        return 0;
    }

    do {
        if (first && (character == '+' || character == '-')) {
            negative = character == '-';
        } else if (isdigit((unsigned char)character)) {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = 1;
            limit = (uintmax_t)INT64_MAX + (negative ? UINTMAX_C(1) : 0);

            if (magnitude > (limit - digit) / UINTMAX_C(10)) {
                valid = 0;
            } else if (valid) {
                magnitude = magnitude * UINTMAX_C(10) + digit;
            }
        } else {
            valid = 0;
        }

        first = 0;
        character = fgetc(stdin);
    } while (character != EOF && !isspace((unsigned char)character));

    if (character == EOF && ferror(stdin)) {
        return 0;
    }

    if (!valid || !has_digit) {
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

static CheckResult records_have_equal_occurrences(const Tuple *tuples,
                                                   size_t count)
{
    Tuple *sorted;
    size_t index;
    size_t expected_frequency = 0;

    if (count == 0) {
        return CHECK_EQUAL;
    }

    if (tuples == NULL || count > SIZE_MAX / sizeof(*sorted)) {
        return CHECK_ERROR;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return CHECK_ERROR;
    }

    for (index = 0; index < count; ++index) {
        sorted[index] = tuples[index];
    }

    qsort(sorted, count, sizeof(*sorted), compare_tuples);

    index = 0;

    while (index < count) {
        size_t end = index + 1;
        size_t frequency;

        while (end < count &&
               tuples_are_equal(&sorted[index], &sorted[end])) {
            ++end;
        }

        frequency = end - index;

        if (expected_frequency == 0) {
            expected_frequency = frequency;
        } else if (frequency != expected_frequency) {
            free(sorted);
            return CHECK_NOT_EQUAL;
        }

        index = end;
    }

    free(sorted);
    return CHECK_EQUAL;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;

    if (!read_size_value(&count)) {
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
        if (!read_int64_value(&tuples[index].first) ||
            !read_int64_value(&tuples[index].second)) {
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