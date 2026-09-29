#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    do {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int find_operations(int64_t *values, size_t count,
                           uint64_t *operations)
{
    uint64_t total = 0;
    int64_t target;

    if (values == NULL || operations == NULL || count == 0) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_int64);
    target = values[count / 2];

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference = absolute_difference(values[i], target);

        if (difference > UINT64_MAX - total) {
            return -1;
        }

        total += difference;
    }

    *operations = total;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t operations;
    int64_t *values;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (find_operations(values, count, &operations) != 0) {
        fputs("Unable to calculate operations\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", operations) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}