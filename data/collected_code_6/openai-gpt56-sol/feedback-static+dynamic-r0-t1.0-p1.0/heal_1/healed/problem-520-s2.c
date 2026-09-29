#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t current;

    if (values == NULL || result == NULL || count == 0U) {
        return 0;
    }

    current = values[0];

    for (size_t i = 1U; i < count; ++i) {
        uint64_t divisor;
        uint64_t quotient;

        if (current == 0U || values[i] == 0U) {
            current = 0U;
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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return 0;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    do {
        if (length + 1U >= size) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' &&
                     ch != '\v');
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' &&
             ch != '\n' && ch != '\r' && ch != '\f' &&
             ch != '\v');

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0U || parsed > SIZE_MAX) {
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
        text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
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
    char token[64];
    size_t count;
    uint64_t *values;
    uint64_t result;

    if (!read_token(token, sizeof(token)) ||
        !parse_size(token, &count) ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_uint64(token, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!lcm_array(values, count, &result)) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}