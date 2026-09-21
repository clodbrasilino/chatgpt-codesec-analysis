#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_token(char **buffer)
{
    size_t length = 0;
    size_t capacity = 32;
    char *token;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    token = malloc(capacity);
    if (token == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(token);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(token, new_capacity);
            if (resized == NULL) {
                free(token);
                return 0;
            }

            token = resized;
            capacity = new_capacity;
        }

        token[length++] = (char)ch;
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        free(token);
        return 0;
    }

    token[length] = '\0';
    *buffer = token;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;
    int success = 0;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '+' || buffer[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    success = 1;

cleanup:
    free(buffer);
    return success;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;
    int success = 0;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    success = 1;

cleanup:
    free(buffer);
    return success;
}

static int64_t saturating_add_positive(int64_t value, int64_t increment)
{
    if (increment > 0 && value > INT64_MAX - increment) {
        return INT64_MAX;
    }

    return value + increment;
}

static int64_t max_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t count)
{
    int64_t previous = 0;
    int64_t previous_previous = 0;

    if (count != 0 && (top == NULL || bottom == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include = previous_previous;
        int64_t current;

        if (column_max > 0) {
            include = saturating_add_positive(include, column_max);
        }

        current = previous > include ? previous : include;
        previous_previous = previous;
        previous = current;
    }

    return previous;
}

int main(void)
{
    size_t count;
    int64_t *top = NULL;
    int64_t *bottom = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_size(&count)) {
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*top)) {
        goto cleanup;
    }

    if (count > 0) {
        top = malloc(count * sizeof(*top));
        if (top == NULL) {
            goto cleanup;
        }

        bottom = malloc(count * sizeof(*bottom));
        if (bottom == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&top[i])) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&bottom[i])) {
            goto cleanup;
        }
    }

    result = max_non_adjacent_sum(top, bottom, count);

    if (printf("%" PRId64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(bottom);
    free(top);
    return status;
}