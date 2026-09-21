#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return 0;
    }

    while (*binary != '\0') {
        unsigned int bit;

        if (*binary != '0' && *binary != '1') {
            return 0;
        }

        bit = (unsigned int)(*binary - '0');

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++binary;
    }

    *decimal = value;
    return 1;
}

static int read_binary(char **input)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;

    if (input == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        perror("Failed to allocate input buffer");
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                perror("Failed to read input");
                free(buffer);
                return 0;
            }

            if (length == 0) {
                fputs("No input provided\n", stderr);
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too long\n", stderr);
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                perror("Failed to grow input buffer");
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *input = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    uint64_t decimal;

    if (!read_binary(&input)) {
        return EXIT_FAILURE;
    }

    if (!binary_to_decimal(input, &decimal)) {
        fputs("Invalid or out-of-range binary number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}