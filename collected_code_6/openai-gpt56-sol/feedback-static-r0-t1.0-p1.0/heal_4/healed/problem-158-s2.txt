#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    size_t capacity = 32U;
    size_t length = 0U;
    char *buffer;
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

    for (;;) {
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
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
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '+' || buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed != UINTMAX_C(0) &&
            parsed <= (uintmax_t)SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(buffer);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= (intmax_t)INT64_MIN &&
            parsed <= (intmax_t)INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(buffer);
    return valid;
}

static uint64_t absolute_difference(int64_t left, int64_t right)
{
    const uint64_t unsigned_left = (uint64_t)left;
    const uint64_t unsigned_right = (uint64_t)right;

    if (left >= right) {
        return unsigned_left - unsigned_right;
    }

    return unsigned_right - unsigned_left;
}

static int calculate_operations(int64_t *values, size_t count,
                                uint64_t *operations)
{
    uint64_t total = UINT64_C(0);
    int64_t target;

    if (values == NULL || operations == NULL || count == 0U) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_int64);
    target = values[count / 2U];

    for (size_t i = 0U; i < count; ++i) {
        uint64_t difference = absolute_difference(values[i], target);

        if (difference > UINT64_MAX - total) {
            return 0;
        }

        total += difference;
    }

    *operations = total;
    return 1;
}

int main(void)
{
    size_t count;
    int64_t *values;
    uint64_t operations;

    if (!read_size(&count) ||
        count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_int64(&values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!calculate_operations(values, count, &operations)) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", operations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}