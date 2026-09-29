#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t lcm = UINT64_C(1);
    size_t i;

    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        uint64_t divisor;
        uint64_t reduced;

        if (values[i] == UINT64_C(0)) {
            *result = UINT64_C(0);
            return 0;
        }

        divisor = gcd_u64(lcm, values[i]);
        reduced = lcm / divisor;

        if (reduced > UINT64_MAX / values[i]) {
            return -1;
        }

        lcm = reduced * values[i];
    }

    *result = lcm;
    return 0;
}

static int read_token(char **token)
{
    enum { MAX_TOKEN_LENGTH = 1024 };
    char local[MAX_TOKEN_LENGTH + 2U];
    char *buffer;
    size_t length;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch) != 0);

    length = 0U;

    while (ch != EOF && isspace((unsigned char)ch) == 0) {
        if (length >= MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && isspace((unsigned char)ch) == 0);

            return -1;
        }

        local[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin) != 0) {
        return -1;
    }

    local[length] = '\0';

    buffer = malloc(length + 1U);
    if (buffer == NULL) {
        return -1;
    }

    for (size_t i = 0U; i <= length; ++i) {
        buffer[i] = local[i];
    }

    *token = buffer;
    return 0;
}

static int parse_uintmax(uintmax_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        goto cleanup;
    }

    *value = parsed;
    result = 0;

cleanup:
    free(buffer);
    return result;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax(&parsed) != 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_u64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax(&parsed) != 0 ||
        parsed > (uintmax_t)UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t *values = NULL;
    uint64_t result;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0 || count == 0U) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (read_u64(&values[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            goto cleanup;
        }
    }

    if (lcm_array(values, count, &result) != 0) {
        fputs("LCM calculation failed due to overflow\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output failed\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}