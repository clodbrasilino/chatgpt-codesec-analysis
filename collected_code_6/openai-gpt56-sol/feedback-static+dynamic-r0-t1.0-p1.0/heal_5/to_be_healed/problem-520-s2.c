#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t current;

    if (values == NULL || result == NULL || count == 0) {
        return 0;
    }

    current = values[0];

    for (size_t i = 1; i < count; ++i) {
        uint64_t divisor;
        uint64_t quotient;

        if (current == 0 || values[i] == 0) {
            current = 0;
            continue;
        }

        divisor = gcd_uint64(current, values[i]);
        quotient = current / divisor;

        if (quotient > UINT64_MAX / values[i]) {
            return 0;
        }

        current = quotient * values[i];
    }

    *result = current;
    return 1;
}

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    enum { TOKEN_LIMIT = 4096 };
    char *buffer;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    buffer = malloc((size_t)TOKEN_LIMIT + 1);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !is_space_char(ch)) {
        if (length >= TOKEN_LIMIT) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && !is_space_char(ch));

            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    char *token = NULL;
    uint64_t *values = NULL;
    uint64_t result;
    size_t count;

    if (!read_token(&token) || !parse_size(token, &count)) {
        free(token);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(&token) || !parse_uint64(token, &values[i])) {
            free(token);
            free(values);
            fputs(ferror(stdin) ? "Input error\n" : "Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    if (read_token(&token)) {
        free(token);
        free(values);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (ferror(stdin)) {
        free(values);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lcm_array(values, count, &result)) {
        free(values);
        fputs("LCM overflow\n", stderr);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}