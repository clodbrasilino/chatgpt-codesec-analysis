#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_ways(size_t n, uint64_t k, uint64_t *result)
{
    uint64_t same;
    uint64_t different;

    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    if (n == 1) {
        *result = k;
        return 1;
    }

    if (k - 1 > UINT64_MAX / k) {
        return 0;
    }

    same = k;
    different = k * (k - 1);

    for (size_t i = 3; i <= n; ++i) {
        uint64_t total;

        if (same > UINT64_MAX - different) {
            return 0;
        }

        total = same + different;

        if (k > 1 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static void skip_space(const char **cursor)
{
    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\r' ||
           **cursor == '\v' || **cursor == '\f') {
        ++*cursor;
    }
}

static int parse_uintmax(const char **cursor, uintmax_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    skip_space(cursor);

    if (**cursor == '\0' || **cursor == '+' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (errno == ERANGE || end == *cursor) {
        return 0;
    }

    *cursor = end;
    *value = parsed;
    return 1;
}

static int read_values(size_t *n, uint64_t *k)
{
    char *line = NULL;
    const char *cursor;
    uintmax_t n_value;
    uintmax_t k_value;
    int valid = 0;

    if (n == NULL || k == NULL || !read_line(&line)) {
        return 0;
    }

    cursor = line;

    if (parse_uintmax(&cursor, &n_value) &&
        parse_uintmax(&cursor, &k_value)) {
        skip_space(&cursor);

        if (*cursor == '\0' &&
            n_value != 0 &&
            n_value <= SIZE_MAX &&
            k_value != 0 &&
            k_value <= UINT64_MAX) {
            *n = (size_t)n_value;
            *k = (uint64_t)k_value;
            valid = 1;
        }
    }

    free(line);
    return valid;
}

int main(void)
{
    size_t n;
    uint64_t k;
    uint64_t result;

    if (!read_values(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}