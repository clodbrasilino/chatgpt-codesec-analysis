#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int product_remainder(const uint64_t *values,
                             size_t count,
                             uint64_t modulus,
                             uint64_t *remainder)
{
    uint64_t result;

    if (remainder == NULL || modulus == 0 ||
        (count != 0 && values == NULL)) {
        return -1;
    }

    result = UINT64_C(1) % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, values[i], modulus);
    }

    *remainder = result;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = 64;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_uint64(FILE *stream, uint64_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (stream == NULL || value == NULL || read_line(stream, &buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > UINT64_MAX) {
        free(buffer);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(buffer);
    return 0;
}

int main(void)
{
    uint64_t count_input;
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;
    size_t count;

    if (read_uint64(stdin, &count_input) != 0 ||
        count_input > SIZE_MAX ||
        read_uint64(stdin, &modulus) != 0 ||
        modulus == 0) {
        return EXIT_FAILURE;
    }

    count = (size_t)count_input;

    if (count > SIZE_MAX / sizeof *values) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof *values);
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_uint64(stdin, &values[i]) != 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (product_remainder(values, count, modulus, &remainder) != 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}