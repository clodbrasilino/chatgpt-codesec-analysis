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

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        char *resized;

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

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

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    uint64_t decimal;
    int status = read_line(&input);

    if (status < 0) {
        return 1;
    }

    if (status == 0) {
        return 0;
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