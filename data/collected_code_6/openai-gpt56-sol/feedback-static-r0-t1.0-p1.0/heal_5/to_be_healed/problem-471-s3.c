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

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return -1;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return -1;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(line, length + 1);

        if (resized == NULL) {
            free(line);
            return -1;
        }

        line = resized;
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 0;
}

int main(void)
{
    uint64_t count_input;
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;
    size_t count;

    if (read_uint64(&count_input) != 0 ||
        count_input > SIZE_MAX ||
        read_uint64(&modulus) != 0 ||
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
        if (read_uint64(&values[i]) != 0) {
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