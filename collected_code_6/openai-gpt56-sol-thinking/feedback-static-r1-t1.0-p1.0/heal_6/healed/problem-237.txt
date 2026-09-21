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
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
} Input;

static int input_init(Input *input, FILE *stream, size_t capacity)
{
    if (input == NULL || stream == NULL || capacity == 0) {
        return 0;
    }

    input->buffer = malloc(capacity);
    if (input->buffer == NULL) {
        return 0;
    }

    input->stream = stream;
    input->capacity = capacity;
    input->position = 0;
    input->length = 0;

    return 1;
}

static void input_destroy(Input *input)
{
    if (input == NULL) {
        return;
    }

    free(input->buffer);
    input->buffer = NULL;
    input->stream = NULL;
    input->capacity = 0;
    input->position = 0;
    input->length = 0;
}

static int input_get(Input *input, int *character)
{
    if (input == NULL || character == NULL || input->stream == NULL ||
        input->buffer == NULL || input->capacity == 0) {
        return -1;
    }

    if (input->length > input->capacity ||
        input->position > input->length) {
        return -1;
    }

    if (input->position == input->length) {
        input->length = fread(input->buffer, 1, input->capacity,
                              input->stream);
        input->position = 0;

        if (input->length == 0) {
            return ferror(input->stream) ? -1 : 0;
        }
    }

    if (input->position >= input->length) {
        return -1;
    }

    *character = (int)input->buffer[input->position];
    ++input->position;

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
    int has_digit = 0;

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

            has_digit = 1;

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
    } while (status == 1 &&
             !isspace((unsigned char)character));

    if (status < 0 || !valid || !has_digit) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_int64_value(Input *input, int64_t *value)
{
    uintmax_t magnitude = 0;
    const uintmax_t positive_limit = (uintmax_t)INT64_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);
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
            uintmax_t limit =
                negative ? negative_limit : positive_limit;

            has_digit = 1;

            if (valid) {
                if (digit > limit ||
                    magnitude > (limit - digit) / UINTMAX_C(10)) {
                    valid = 0;
                } else {
                    magnitude =
                        magnitude * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        first = 0;
        status = input_get(input, &character);
    } while (status == 1 &&
             !isspace((unsigned char)character));

    if (status < 0 || !valid || !has_digit) {
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
    if (left == NULL || right == NULL) {
        return 0;
    }

    return left->first == right->first &&
           left->second == right->second;
}

static CheckResult records_have_equal_occurrences(
    Tuple *tuples, size_t count)
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
    Input input;
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;
    int exit_status = EXIT_FAILURE;

    if (!input_init(&input, stdin, 4096)) {
        fprintf(stderr, "Failed to initialize input.\n");
        return EXIT_FAILURE;
    }

    if (!read_size_value(&input, &count)) {
        fprintf(stderr, "Failed to read the tuple count.\n");
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large.\n");
        goto cleanup;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            goto cleanup;
        }
    }

    for (index = 0; index < count; ++index) {
        if (!read_int64_value(&input, &tuples[index].first) ||
            !read_int64_value(&input, &tuples[index].second)) {
            fprintf(stderr, "Failed to read tuple %zu.\n",
                    index + 1);
            goto cleanup;
        }
    }

    result = records_have_equal_occurrences(tuples, count);
    if (result == CHECK_ERROR) {
        fprintf(stderr, "Unable to check record occurrences.\n");
        goto cleanup;
    }

    if (puts(result == CHECK_EQUAL ? "YES" : "NO") == EOF) {
        fprintf(stderr, "Failed to write the result.\n");
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    input_destroy(&input);
    return exit_status;
}