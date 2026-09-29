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

    if (**input == '\0' || **input == '+' || **input == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t length;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2U, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *position;
    uint64_t a;
    uint64_t b;
    uint64_t result;

    if (!read_line(&input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    position = input;

    if (!parse_uint64(&position, &a) ||
        !parse_uint64(&position, &b)) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*position)) {
        ++position;
    }

    if (*position != '\0') {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (!lcm(a, b, &result)) {
        fprintf(stderr,
                "Inputs must be positive and the result must fit in uint64_t\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}