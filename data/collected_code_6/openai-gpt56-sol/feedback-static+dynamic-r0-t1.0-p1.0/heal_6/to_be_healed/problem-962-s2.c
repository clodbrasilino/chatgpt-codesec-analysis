#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        half = count / UINT64_C(2);

        if (first > UINT64_MAX - last) {
            return 0;
        }

        factor = first + last;
    } else {
        half = (first / UINT64_C(2)) + (last / UINT64_C(2));
        factor = count;
    }

    if (half != 0 && factor > UINT64_MAX / half) {
        return 0;
    }

    *result = half * factor;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;
    size_t capacity;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    length = 0;
    capacity = 64;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

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

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const unsigned char *p;
    uint64_t number = 0;
    int has_digit = 0;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = (const unsigned char *)*cursor;

    while (*p == ' ' || *p == '\t' || *p == '\r' ||
           *p == '\v' || *p == '\f') {
        ++p;
    }

    while (*p >= '0' && *p <= '9') {
        unsigned int digit = (unsigned int)(*p - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        number = number * UINT64_C(10) + digit;
        has_digit = 1;
        ++p;
    }

    if (!has_digit) {
        return 0;
    }

    *value = number;
    *cursor = (const char *)p;
    return 1;
}

static int read_range(uint64_t *left, uint64_t *right)
{
    char *line = NULL;
    const char *cursor;
    int valid = 0;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (!read_line(&line)) {
        return 0;
    }

    cursor = line;

    if (parse_uint64(&cursor, left) && parse_uint64(&cursor, right)) {
        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
               *cursor == '\v' || *cursor == '\f') {
            ++cursor;
        }

        valid = (*cursor == '\0');
    }

    free(line);
    return valid;
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