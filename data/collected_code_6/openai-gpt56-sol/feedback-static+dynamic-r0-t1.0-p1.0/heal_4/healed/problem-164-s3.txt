#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_proper_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 1;

    if (sum == NULL || number == 0) {
        return 0;
    }

    if (number == 1) {
        *sum = 0;
        return 1;
    }

    for (uint64_t divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t quotient = number / divisor;

            if (result > UINT64_MAX - divisor) {
                return 0;
            }
            result += divisor;

            if (quotient != divisor) {
                if (result > UINT64_MAX - quotient) {
                    return 0;
                }
                result += quotient;
            }
        }
    }

    *sum = result;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '-' || **cursor == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
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

int main(void)
{
    char *input = NULL;
    const char *cursor;
    uint64_t first;
    uint64_t second;
    uint64_t first_sum;
    uint64_t second_sum;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &first) ||
        !parse_uint64(&cursor, &second)) {
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

    if (!sum_of_proper_divisors(first, &first_sum) ||
        !sum_of_proper_divisors(second, &second_sum)) {
        fputs("Unable to calculate divisor sums\n", stderr);
        return EXIT_FAILURE;
    }

    puts(first_sum == second_sum ? "Same" : "Not same");
    return EXIT_SUCCESS;
}