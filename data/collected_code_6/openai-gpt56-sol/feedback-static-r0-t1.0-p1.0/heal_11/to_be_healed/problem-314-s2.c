#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 64;
    size_t length = 0;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t required;
            size_t new_capacity;
            char *new_buffer;

            if (length > SIZE_MAX - 2) {
                free(buffer);
                return 0;
            }

            required = length + 2;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int64_t max_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t n)
{
    int64_t previous = 0;
    int64_t previous_previous = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include = previous_previous;

        if (column_max > 0) {
            if (include > INT64_MAX - column_max) {
                include = INT64_MAX;
            } else {
                include += column_max;
            }
        }

        {
            int64_t current = previous > include ? previous : include;
            previous_previous = previous;
            previous = current;
        }
    }

    return previous;
}

int main(void)
{
    size_t n;
    int64_t *top = NULL;
    int64_t *bottom = NULL;
    int64_t result;

    if (!read_size(&n) || n > SIZE_MAX / sizeof(*top)) {
        return EXIT_FAILURE;
    }

    if (n > 0) {
        top = malloc(n * sizeof(*top));
        bottom = malloc(n * sizeof(*bottom));

        if (top == NULL || bottom == NULL) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&top[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&bottom[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    result = max_non_adjacent_sum(top, bottom, n);

    free(top);
    free(bottom);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}