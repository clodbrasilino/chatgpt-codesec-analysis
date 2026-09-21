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
        int digit = (unsigned char)*begin - '0';

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
    char *buffer = malloc(capacity);
    size_t used = 0;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (used + 1 >= capacity) {
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

        buffer[used++] = (char)ch;
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
    char *input;
    size_t length;
    char *begin;
    char *end;
    char *p;

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

    if (*p != '\0' ||
        (size_t)(end - begin) > (size_t)INT_MAX / 9U + 1U) {
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