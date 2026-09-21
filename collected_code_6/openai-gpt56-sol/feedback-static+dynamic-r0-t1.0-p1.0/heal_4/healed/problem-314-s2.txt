#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int valid = 1;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 < size) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';

    if (ferror(stdin)) {
        return 0;
    }

    return valid;
}

static int read_size(size_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '+' || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof buffer)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || end == NULL || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
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

        if (column_max > 0) {
            include = saturating_add_positive(include, column_max);
        }

        int64_t current = previous > include ? previous : include;
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

    if (!read_size(&count)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof *top) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        top = malloc(count * sizeof *top);
        bottom = malloc(count * sizeof *bottom);

        if (top == NULL || bottom == NULL) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&top[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&bottom[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    result = max_non_adjacent_sum(top, bottom, count);

    if (printf("%" PRId64 "\n", result) < 0) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    free(top);
    free(bottom);
    return EXIT_SUCCESS;
}