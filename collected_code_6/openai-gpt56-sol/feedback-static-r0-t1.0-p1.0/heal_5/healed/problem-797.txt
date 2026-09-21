#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_naturals(int64_t left, int64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || left < 1 || right < left) {
        return 0;
    }

    first = (uint64_t)left;
    last = (uint64_t)right;

    if ((first & UINT64_C(1)) == 0) {
        ++first;
    }

    if ((last & UINT64_C(1)) == 0) {
        --last;
    }

    if (first > last) {
        *result = UINT64_C(0);
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first / UINT64_C(2) + last / UINT64_C(2) + UINT64_C(1);

    if (count > UINT64_MAX / factor) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    const char *cursor;
    int64_t left;
    int64_t right;
    uint64_t sum;
    int ch;
    char *replacement;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Invalid input\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            replacement = realloc(input, new_capacity);
            if (replacement == NULL) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            input = replacement;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (length + 1 > capacity) {
        replacement = realloc(input, length + 1);
        if (replacement == NULL) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
        input = replacement;
    }

    input[length] = '\0';
    cursor = input;

    if (!parse_int64(&cursor, &left) || !parse_int64(&cursor, &right)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_odd_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}