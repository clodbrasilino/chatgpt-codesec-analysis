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
        half = first / UINT64_C(2) + last / UINT64_C(2);
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
    size_t length = 0;
    size_t capacity = 64;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

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

        if (ch == '\0') {
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_horizontal_space(unsigned char ch)
{
    return ch == (unsigned char)' ' ||
           ch == (unsigned char)'\t' ||
           ch == (unsigned char)'\r' ||
           ch == (unsigned char)'\v' ||
           ch == (unsigned char)'\f';
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

    while (is_horizontal_space(*p)) {
        ++p;
    }

    while (*p >= (unsigned char)'0' && *p <= (unsigned char)'9') {
        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

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
    uint64_t parsed_left;
    uint64_t parsed_right;
    int valid = 0;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (!read_line(&line)) {
        return 0;
    }

    cursor = line;

    if (parse_uint64(&cursor, &parsed_left) &&
        parse_uint64(&cursor, &parsed_right)) {
        while (is_horizontal_space((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            *left = parsed_left;
            *right = parsed_right;
            valid = 1;
        }
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