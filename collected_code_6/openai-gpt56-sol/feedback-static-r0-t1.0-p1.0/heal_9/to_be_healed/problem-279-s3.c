#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t factor;

    if (result == NULL || n == 0 || n > UINT64_MAX / UINT64_C(4)) {
        return 0;
    }

    factor = UINT64_C(4) * n - UINT64_C(3);

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

static int read_input(char **buffer)
{
    size_t capacity = 32;
    size_t length = 0;
    char *data;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(data);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        data[length++] = (char)ch;
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t value;
    uint64_t result;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!decagonal_number((uint64_t)value, &result)) {
        free(input);
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}