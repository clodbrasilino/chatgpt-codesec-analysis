#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
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
    uint64_t lcm = 1U;
    size_t i;

    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        uint64_t divisor;
        uint64_t reduced;

        if (values[i] == 0U) {
            *result = 0U;
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
    char *buffer;
    size_t capacity = 32U;
    size_t length = 0U;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch) != 0);

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && isspace((unsigned char)ch) == 0) {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int parse_uintmax(uintmax_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
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

    if (value == NULL || parse_uintmax(&parsed) != 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_u64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || parse_uintmax(&parsed) != 0 ||
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
        fprintf(stderr, "Invalid element count\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Array size is too large\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (read_u64(&values[i]) != 0) {
            fprintf(stderr, "Invalid array element\n");
            goto cleanup;
        }
    }

    if (lcm_array(values, count, &result) != 0) {
        fprintf(stderr, "LCM calculation failed due to overflow\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}