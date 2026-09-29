#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_input(char **input)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == capacity - 1) {
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

    buffer[length] = '\0';
    *input = buffer;
    return 1;
}

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        uint64_t quotient;

        if (number % divisor != 0) {
            continue;
        }

        quotient = number / divisor;

        if ((divisor & UINT64_C(1)) == 0) {
            if (total > UINT64_MAX - divisor) {
                return 0;
            }
            total += divisor;
        }

        if (quotient != divisor && (quotient & UINT64_C(1)) == 0) {
            if (total > UINT64_MAX - quotient) {
                return 0;
            }
            total += quotient;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t sum;

    if (!read_input(&input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (is_space_char(*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_char(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_even_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}