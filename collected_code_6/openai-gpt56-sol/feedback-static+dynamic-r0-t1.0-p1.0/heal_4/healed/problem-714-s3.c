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

static int is_space_character(char character)
{
    return character == ' ' ||
           character == '\t' ||
           character == '\r' ||
           character == '\n' ||
           character == '\v' ||
           character == '\f';
}

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t length;

    errno = 0;
    length = getline(&buffer, &capacity, stdin);

    if (length < 0) {
        free(buffer);
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *start = input;

    while (is_space_character(*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    printf("%zu\n",
           count_distinct_prime_power_factors((uint64_t)value));

    return EXIT_SUCCESS;
}