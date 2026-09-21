#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int read_token(char **buffer)
{
    char *data;
    size_t capacity = 32U;
    size_t length = 0U;
    int ch;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;

    for (;;) {
        ch = getchar();

        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            temporary = realloc(data, new_capacity);
            if (temporary == NULL) {
                free(data);
                return -1;
            }

            data = temporary;
            capacity = new_capacity;
        }

        data[length++] = (char)ch;

        ch = getchar();
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(data);
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

static int read_uintmax(uintmax_t maximum, int allow_zero, uintmax_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int token_status;

    if (value == NULL) {
        return -1;
    }

    token_status = read_token(&buffer);
    if (token_status != 1) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > maximum || (!allow_zero && parsed == UINTMAX_C(0))) {
        free(buffer);
        return -1;
    }

    free(buffer);
    *value = parsed;
    return 0;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        read_uintmax((uintmax_t)SIZE_MAX, 0, &parsed) != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_u64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        read_uintmax((uintmax_t)UINT64_MAX, 1, &parsed) != 0) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t *values, size_t count, uint64_t *result)
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

int main(void)
{
    size_t count;
    uint64_t *values = NULL;
    uint64_t result;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size(&count) != 0) {
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
        fputs("LCM calculation failed due to invalid input or overflow\n",
              stderr);
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