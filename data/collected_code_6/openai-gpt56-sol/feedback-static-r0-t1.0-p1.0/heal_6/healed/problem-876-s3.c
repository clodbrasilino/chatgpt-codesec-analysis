#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

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
    const char *position;
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    position = *input;

    while (isspace((unsigned char)*position)) {
        ++position;
    }

    if (*position == '\0' || *position == '+' || *position == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(position, &end, 10);

    if (end == position || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int discard_line(void)
{
    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            return 1;
        }

        if (ch == EOF) {
            return ferror(stdin) == 0;
        }
    }
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    for (length = 0; buffer[length] != '\0' && buffer[length] != '\n';
         ++length) {
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (!discard_line()) {
            free(buffer);
            return 0;
        }

        free(buffer);
        return 0;
    } else if (length == (size_t)MAX_INPUT_LENGTH && !feof(stdin)) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
        } else if (ch != '\n') {
            if (!discard_line()) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    position = input;

    if (!parse_uint64(&position, &a) ||
        !parse_uint64(&position, &b)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*position)) {
        ++position;
    }

    if (*position != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!lcm(a, b, &result)) {
        fputs("Inputs must be positive and the result must fit in uint64_t\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}