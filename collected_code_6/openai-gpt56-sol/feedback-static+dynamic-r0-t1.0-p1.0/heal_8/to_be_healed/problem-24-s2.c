#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    const unsigned char *p;
    uint64_t result = 0;
    int has_digit = 0;

    if (binary == NULL || decimal == NULL) {
        return 0;
    }

    p = (const unsigned char *)binary;

    while (*p != '\0' && isspace((int)*p)) {
        ++p;
    }

    while (*p == (unsigned char)'0' || *p == (unsigned char)'1') {
        uint64_t bit = (uint64_t)(*p - (unsigned char)'0');

        has_digit = 1;

        if (result > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        result = result * UINT64_C(2) + bit;
        ++p;
    }

    if (!has_digit) {
        return 0;
    }

    while (*p != '\0' && isspace((int)*p)) {
        ++p;
    }

    if (*p != '\0') {
        return 0;
    }

    *decimal = result;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
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
                return NULL;
            }
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    uint64_t decimal;

    input = read_line(stdin);
    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (!binary_to_decimal(input, &decimal)) {
        free(input);

        if (fputs("Invalid binary number\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}