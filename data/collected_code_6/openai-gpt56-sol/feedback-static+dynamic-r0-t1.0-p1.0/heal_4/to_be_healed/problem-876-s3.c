#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uint64_t a, uint64_t b, uint64_t *result)
{
    uint64_t quotient;

    if (a == 0 || b == 0 || result == NULL) {
        return 0;
    }

    quotient = a / gcd(a, b);

    if (quotient > UINT64_MAX / b) {
        return 0;
    }

    *result = quotient * b;
    return 1;
}

static int read_line(char **buffer)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *line = malloc(capacity);

    if (line == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *resized;

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            capacity *= 2;
            resized = realloc(line, capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
        }

        line[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(line);
        return 0;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char *line = NULL;
    const char *cursor;
    uint64_t a;
    uint64_t b;
    uint64_t result;

    if (!read_line(&line)) {
        fprintf(stderr, "Unable to read input\n");
        return EXIT_FAILURE;
    }

    cursor = line;

    if (!parse_uint64(&cursor, &a) || !parse_uint64(&cursor, &b)) {
        free(line);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(line);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    free(line);

    if (!lcm(a, b, &result)) {
        fprintf(stderr,
                "Inputs must be positive and the result must fit in uint64_t\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}