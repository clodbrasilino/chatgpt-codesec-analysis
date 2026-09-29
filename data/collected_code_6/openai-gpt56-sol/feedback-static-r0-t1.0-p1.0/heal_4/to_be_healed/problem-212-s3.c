#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = 30;
    uint64_t value = 1;

    if (result == NULL || n == 0 || n > 4934) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + 1;
    factors[2] = 2 * n + 1;
    factors[3] = 3 * n * n + 3 * n - 1;

    for (size_t i = 0; i < 4 && divisor > 1; ++i) {
        for (uint64_t candidate = 2; candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 &&
                   factors[i] % candidate == 0) {
                divisor /= candidate;
                factors[i] /= candidate;
            }
        }
    }

    if (divisor != 1) {
        return 0;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

static int read_line(char **line)
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

            if (ch == EOF && length == 0) {
                free(buffer);
                return 0;
            }

            break;
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

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (printf("Enter n: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > 4934) {
        free(input);
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_fourth_powers((uint64_t)parsed, &result)) {
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}