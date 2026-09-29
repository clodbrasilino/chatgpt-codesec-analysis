#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (result > UINT64_MAX - divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (result > UINT64_MAX - paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
}

static int read_line(char **buffer)
{
    size_t capacity = 32;
    size_t length = 0;
    char *line;
    int ch = EOF;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(line);
        return 0;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t value;
    uint64_t number;
    uint64_t sum;
    int status = EXIT_FAILURE;

    if (fputs("Enter a positive integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&input)) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value == 0 ||
        value > (uintmax_t)UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        goto cleanup;
    }

    number = (uint64_t)value;

    if (!sum_of_divisors(number, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}