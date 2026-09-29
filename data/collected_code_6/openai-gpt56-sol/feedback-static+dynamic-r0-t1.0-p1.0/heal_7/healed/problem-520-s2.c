#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { TOKEN_LIMIT = 4096 };

enum ReadStatus {
    READ_OK,
    READ_EOF,
    READ_TOO_LONG,
    READ_ERROR,
    READ_NO_MEMORY
};

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

static enum ReadStatus read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return READ_ERROR;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return ferror(stdin) ? READ_ERROR : READ_EOF;
        }
    } while (is_space_char(ch));

    buffer = malloc((size_t)TOKEN_LIMIT + 1U);
    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    while (ch != EOF && !is_space_char(ch)) {
        if (length == (size_t)TOKEN_LIMIT) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !is_space_char(ch));

            free(buffer);

            if (ch == EOF && ferror(stdin)) {
                return READ_ERROR;
            }

            return READ_TOO_LONG;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return READ_ERROR;
    }

    buffer[length] = '\0';
    *token = buffer;
    return READ_OK;
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

static int report_read_failure(enum ReadStatus status)
{
    if (status == READ_ERROR) {
        fputs("Input error\n", stderr);
    } else if (status == READ_NO_MEMORY) {
        fputs("Memory allocation failed\n", stderr);
    } else {
        fputs("Invalid input\n", stderr);
    }

    return EXIT_FAILURE;
}

int main(void)
{
    char *token = NULL;
    uint64_t *values = NULL;
    uint64_t result;
    size_t count;
    enum ReadStatus status;

    status = read_token(&token);
    if (status != READ_OK) {
        return report_read_failure(status);
    }

    if (!parse_size(token, &count)) {
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
        status = read_token(&token);
        if (status != READ_OK) {
            free(values);
            return report_read_failure(status);
        }

        if (!parse_uint64(token, &values[i])) {
            free(token);
            free(values);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    status = read_token(&token);
    if (status == READ_OK) {
        free(token);
        free(values);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != READ_EOF) {
        free(values);
        return report_read_failure(status);
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