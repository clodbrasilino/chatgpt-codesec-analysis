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
    int has_digits = 0;

    if (binary == NULL || decimal == NULL) {
        return 0;
    }

    p = (const unsigned char *)binary;

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    while (*p == '0' || *p == '1') {
        uint64_t bit = (uint64_t)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        result = result * UINT64_C(2) + bit;
        has_digits = 1;
        ++p;
    }

    if (!has_digits) {
        return 0;
    }

    while (*p != '\0' && isspace(*p)) {
        ++p;
    }

    if (*p != '\0') {
        return 0;
    }

    *decimal = result;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    uint64_t decimal;
    int status;

    status = read_line(&input);
    if (status < 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (!binary_to_decimal(input, &decimal)) {
        free(input);
        fputs("Invalid binary number\n", stderr);
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