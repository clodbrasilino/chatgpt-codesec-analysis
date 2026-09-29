#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_distinct_prime_power_factors(uint64_t number)
{
    size_t count = 0;

    if (number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        ++count;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t divisor = 3;
         divisor <= number / divisor;
         divisor += 2) {
        if (number % divisor == 0) {
            ++count;
            do {
                number /= divisor;
            } while (number % divisor == 0);
        }
    }

    if (number > 1) {
        ++count;
    }

    return count;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

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

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    uintmax_t value;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n",
           count_distinct_prime_power_factors((uint64_t)value));

    free(input);
    return EXIT_SUCCESS;
}