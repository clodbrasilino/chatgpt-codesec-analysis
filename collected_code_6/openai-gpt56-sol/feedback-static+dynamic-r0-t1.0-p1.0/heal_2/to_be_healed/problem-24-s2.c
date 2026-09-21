#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t result = 0;
    const unsigned char *p;

    if (binary == NULL || decimal == NULL) {
        return 0;
    }

    p = (const unsigned char *)binary;

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '\0') {
        return 0;
    }

    while (*p == '0' || *p == '1') {
        uint64_t bit = (uint64_t)(*p - (unsigned char)'0');

        if (result > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        result = result * UINT64_C(2) + bit;
        ++p;
    }

    while (isspace(*p)) {
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
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
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
        return ferror(stdin) ? 1 : 0;
    }

    if (!binary_to_decimal(input, &decimal)) {
        free(input);
        fputs("Invalid binary number\n", stderr);
        return 1;
    }

    free(input);

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        return 1;
    }

    if (fflush(stdout) == EOF) {
        return 1;
    }

    return 0;
}