#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *result)
{
    uint64_t sum = UINT64_C(1);

    if (number == 0 || result == NULL) {
        return 0;
    }

    while ((number & UINT64_C(1)) == 0) {
        number >>= 1;
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= number / factor;
         factor += UINT64_C(2)) {
        uint64_t term = UINT64_C(1);
        uint64_t power = UINT64_C(1);

        while (number % factor == 0) {
            number /= factor;

            if (power > UINT64_MAX / factor) {
                return 0;
            }
            power *= factor;

            if (term > UINT64_MAX - power) {
                return 0;
            }
            term += power;
        }

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    if (number > UINT64_C(1)) {
        uint64_t term;

        if (number == UINT64_MAX) {
            return 0;
        }

        term = number + UINT64_C(1);

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    *result = sum;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int character = EOF;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length >= capacity - 1) {
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

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return 0;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *input = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&input)) {
        return 0;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        free(input);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(input);
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (!read_uint64(&number)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors(number, &result)) {
        fputs("The sum cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}