#include <ctype.h>
#include <errno.h>
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
        int digit = (int)((unsigned char)*begin - (unsigned char)'0');

        if ((digit % 2) == 0) {
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
    int ch = EOF;

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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used >= capacity - 1) {
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

    if (ferror(stdin) || (ch == EOF && used == 0)) {
        free(buffer);
        return 0;
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
    char *begin;
    char *end;
    char *p;
    size_t token_length;
    size_t maximum_digits = (size_t)INT_MAX / 9U;

    if (!read_line(&input, &length)) {
        return EXIT_FAILURE;
    }

    begin = input;
    while (*begin != '\0' && isspace((unsigned char)*begin)) {
        ++begin;
    }

    errno = 0;
    (void)strtoll(begin, &end, 10);

    if (errno == ERANGE || end == begin) {
        free(input);
        return EXIT_FAILURE;
    }

    p = end;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        ++p;
    }

    token_length = (size_t)(end - begin);

    if (*p != '\0' ||
        token_length > maximum_digits + 1U) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", digit_sum_difference(begin, end)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}