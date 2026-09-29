#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    enum {
        INITIAL_CAPACITY = 32,
        MAX_TOKEN_LENGTH = 1024
    };

    char *buffer;
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= MAX_TOKEN_LENGTH + 1) {
                free(buffer);
                return 0;
            }

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            if (new_capacity > MAX_TOKEN_LENGTH + 1) {
                new_capacity = MAX_TOKEN_LENGTH + 1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int success = 0;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    success = 1;

cleanup:
    free(token);
    return success;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int success = 0;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    success = 1;

cleanup:
    free(token);
    return success;
}

static int read_int_value(int *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int success = 0;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        goto cleanup;
    }

    *value = (int)parsed;
    success = 1;

cleanup:
    free(token);
    return success;
}

static int add_pair_count(uint64_t *total, uint64_t amount)
{
    if (total == NULL || amount > UINT64_MAX - *total) {
        return 0;
    }

    *total += amount;
    return 1;
}

static int choose_two(size_t count, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || (uintmax_t)count > UINT64_MAX) {
        return 0;
    }

    if (count < 2) {
        *result = 0;
        return 1;
    }

    a = (uint64_t)count;
    b = a - 1;

    if ((a & UINT64_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (b > UINT64_MAX / a) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int count_pairs(int *values, size_t count, int64_t target,
                       uint64_t *result)
{
    size_t left = 0;
    size_t right;
    uint64_t pairs = 0;

    if (result == NULL) {
        return 0;
    }

    *result = 0;

    if (count < 2) {
        return 1;
    }

    if (values == NULL) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);
    right = count - 1;

    while (left < right) {
        int64_t current =
            (int64_t)values[left] + (int64_t)values[right];

        if (current < target) {
            ++left;
        } else if (current > target) {
            --right;
        } else if (values[left] == values[right]) {
            uint64_t amount;

            if (!choose_two(right - left + 1, &amount) ||
                !add_pair_count(&pairs, amount)) {
                return 0;
            }

            break;
        } else {
            size_t left_count = 1;
            size_t right_count = 1;
            uint64_t left_amount;
            uint64_t right_amount;
            uint64_t amount;

            while (left_count < right - left &&
                   values[left + left_count] == values[left]) {
                ++left_count;
            }

            while (right_count < right - left &&
                   values[right - right_count] == values[right]) {
                ++right_count;
            }

            if ((uintmax_t)left_count > UINT64_MAX ||
                (uintmax_t)right_count > UINT64_MAX) {
                return 0;
            }

            left_amount = (uint64_t)left_count;
            right_amount = (uint64_t)right_count;

            if (right_amount > UINT64_MAX / left_amount) {
                return 0;
            }

            amount = left_amount * right_amount;

            if (!add_pair_count(&pairs, amount)) {
                return 0;
            }

            left += left_count;
            right -= right_count;
        }
    }

    *result = pairs;
    return 1;
}

int main(void)
{
    size_t count;
    int64_t target;
    int *values = NULL;
    uint64_t result;

    if (!read_size(&count) || !read_int64_value(&target)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values) ||
        (uintmax_t)count > UINT64_MAX) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int_value(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_pairs(values, count, target, &result)) {
        fputs("Pair count is too large\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}