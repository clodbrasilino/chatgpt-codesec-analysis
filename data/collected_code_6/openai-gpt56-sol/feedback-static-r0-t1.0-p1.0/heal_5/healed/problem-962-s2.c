#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int read_range(uint64_t *left, uint64_t *right)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    const char *cursor;

    if (left == NULL || right == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(input);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 0;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return 0;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return 0;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            free(input);
            return 0;
        }

        new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            free(input);
            return 0;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';
    cursor = input;

    if (!parse_uint64(&cursor, left) ||
        !parse_uint64(&cursor, right)) {
        free(input);
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        return 0;
    }

    free(input);
    return 1;
}

static int sum_even_natural_numbers(uint64_t left, uint64_t right,
                                    uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half;
    uint64_t factor;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    first = left;

    if ((first & UINT64_C(1)) != 0) {
        if (first == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        ++first;
    }

    last = right - (right & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        half = count / UINT64_C(2);

        if (first > UINT64_MAX - last) {
            return 0;
        }

        factor = first + last;
    } else {
        half = first / UINT64_C(2) + last / UINT64_C(2);
        factor = count;
    }

    if (half != 0 && factor > UINT64_MAX / half) {
        return 0;
    }

    *result = half * factor;
    return 1;
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_range(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_natural_numbers(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}