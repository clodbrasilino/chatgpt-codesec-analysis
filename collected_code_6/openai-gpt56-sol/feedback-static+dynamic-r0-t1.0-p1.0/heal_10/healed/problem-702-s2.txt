#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t minimum_removals(int *values, size_t count, int64_t k)
{
    if (values == NULL || count == 0) {
        return 0;
    }

    if (k < 0) {
        return count;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    size_t left = 0;
    size_t max_kept = 1;

    for (size_t right = 0; right < count; ++right) {
        while (left < right &&
               (int64_t)values[right] - (int64_t)values[left] > k) {
            ++left;
        }

        const size_t kept = right - left + 1;

        if (kept > max_kept) {
            max_kept = kept;
        }
    }

    return count - max_kept;
}

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static char *read_token(void)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    int ch;

    do {
        ch = getchar();

        if (ch == EOF) {
            free(buffer);
            return NULL;
        }
    } while (is_space_char(ch));

    for (;;) {
        if (ch == EOF || is_space_char(ch)) {
            break;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            const size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static int parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || *text == '+') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    const intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int parse_int(const char *text, int *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    const intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(void)
{
    size_t count = 0;
    int64_t k = 0;
    char *token = read_token();

    if (token == NULL || !parse_size(token, &count)) {
        free(token);
        return EXIT_FAILURE;
    }

    free(token);
    token = read_token();

    if (token == NULL || !parse_int64(token, &k)) {
        free(token);
        return EXIT_FAILURE;
    }

    free(token);

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        token = read_token();

        if (token == NULL || !parse_int(token, &values[i])) {
            free(token);
            free(values);
            return EXIT_FAILURE;
        }

        free(token);
    }

    const size_t result = minimum_removals(values, count, k);

    if (printf("%zu\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}