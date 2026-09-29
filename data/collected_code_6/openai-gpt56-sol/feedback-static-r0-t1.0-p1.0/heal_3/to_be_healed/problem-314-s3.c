#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

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

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int only_trailing_space(const char *text)
{
    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int read_int64(int64_t *value)
{
    char *line;
    char *start;
    char *end;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end ||
        errno == ERANGE ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(line);
        return 0;
    }

    *value = (int64_t)parsed;
    free(line);
    return 1;
}

static int read_size(size_t *value)
{
    char *line;
    char *start;
    char *end;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end ||
        errno == ERANGE ||
        parsed > SIZE_MAX ||
        !only_trailing_space(end)) {
        free(line);
        return 0;
    }

    *value = (size_t)parsed;
    free(line);
    return 1;
}

static int64_t saturating_add(int64_t left, int64_t right)
{
    if (right > 0 && left > INT64_MAX - right) {
        return INT64_MAX;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return INT64_MIN;
    }

    return left + right;
}

static int64_t max_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t n)
{
    int64_t previous = 0;
    int64_t current = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include = saturating_add(previous, column_max);
        int64_t next = include > current ? include : current;

        previous = current;
        current = next;
    }

    return current;
}

int main(void)
{
    size_t n;
    int64_t *top = NULL;
    int64_t *bottom = NULL;

    if (!read_size(&n) || n > SIZE_MAX / sizeof(*top)) {
        return EXIT_FAILURE;
    }

    if (n != 0) {
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

    int64_t result = max_non_adjacent_sum(top, bottom, n);

    free(top);
    free(bottom);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}