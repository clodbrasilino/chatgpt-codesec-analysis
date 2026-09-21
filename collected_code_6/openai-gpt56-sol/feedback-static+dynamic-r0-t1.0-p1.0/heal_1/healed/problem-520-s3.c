#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    do {
        if (length + 1U >= size) {
            while ((ch = getchar()) != EOF && !isspace((unsigned char)ch)) {
            }
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_u64(uint64_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
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
        fprintf(stderr, "LCM calculation failed due to invalid input or overflow\n");
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