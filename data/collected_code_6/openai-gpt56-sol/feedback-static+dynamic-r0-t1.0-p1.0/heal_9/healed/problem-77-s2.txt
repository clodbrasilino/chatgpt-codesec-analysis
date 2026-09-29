#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = (int)(*begin - '0');

        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }

        ++begin;
    }

    return even_sum - odd_sum;
}

static int read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (line == NULL || length == NULL) {
        return 0;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (used == capacity - 1) {
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

        buffer[used++] = (char)(unsigned char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *begin;
    const char *end;
    const char *p;
    size_t digit_count = 0;
    size_t maximum_digits = (size_t)INT_MAX / 9U;
    int result;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    begin = input;
    end = input + length;

    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++digit_count;
        ++begin;
    }

    p = begin;
    while (p < end && isdigit((unsigned char)*p)) {
        ++digit_count;
        ++p;
    }

    if (p == begin) {
        free(input);
        return EXIT_FAILURE;
    }

    while (p < end && isspace((unsigned char)*p)) {
        ++p;
    }

    if (p != end || digit_count > maximum_digits + 1U) {
        free(input);
        return EXIT_FAILURE;
    }

    begin = input;
    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    end = begin + digit_count;
    result = digit_sum_difference(begin, end);

    if (printf("%d\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}