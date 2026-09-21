#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = UINT64_C(30);
    uint64_t value = UINT64_C(1);
    size_t i;

    if (result == NULL || n == 0 || n > UINT64_C(92681)) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + UINT64_C(1);
    factors[2] = UINT64_C(2) * n + UINT64_C(1);
    factors[3] = UINT64_C(3) * n * n + UINT64_C(3) * n - UINT64_C(1);

    for (i = 0; i < sizeof factors / sizeof factors[0]; ++i) {
        uint64_t factor = factors[i];
        uint64_t candidate;

        for (candidate = UINT64_C(2);
             candidate <= divisor / candidate;
             ++candidate) {
            while (divisor % candidate == 0 &&
                   factor % candidate == 0) {
                divisor /= candidate;
                factor /= candidate;
            }
        }

        if (divisor > 1 && factor % divisor == 0) {
            factor /= divisor;
            divisor = 1;
        }

        factors[i] = factor;
    }

    if (divisor != 1) {
        return 0;
    }

    for (i = 0; i < sizeof factors / sizeof factors[0]; ++i) {
        if (value > UINT64_MAX / factors[i]) {
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
    char *buffer;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
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

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    if (ch == EOF && length == 0) {
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
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (parsed == 0 || parsed > UINT64_C(92681) ||
        !sum_fourth_powers((uint64_t)parsed, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}