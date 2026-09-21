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

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    char *buffer;
    size_t capacity = 32U;
    size_t length = 0U;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !is_space_char(ch)) {
        if (length == capacity - 1U) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
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
        text[0] == '-') {
        return 0;
    }

    errno = 0;
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
    size_t count;
    uint64_t *values;
    uint64_t result;

    if (!read_token(&token)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_size(token, &count) ||
        count > SIZE_MAX / sizeof(*values)) {
        free(token);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_token(&token) ||
            !parse_uint64(token, &values[i])) {
            free(token);
            free(values);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    if (!lcm_array(values, count, &result)) {
        free(values);
        fputs("LCM overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}