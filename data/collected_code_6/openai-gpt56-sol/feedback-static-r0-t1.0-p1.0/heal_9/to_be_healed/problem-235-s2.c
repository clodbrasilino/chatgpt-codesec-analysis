#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_even_bits(uint32_t value)
{
    return value | UINT32_C(0x55555555);
}

static int read_line(char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    char *line = malloc(capacity);

    if (buffer == NULL || line == NULL) {
        free(line);
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    uintmax_t parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint32_t result = set_even_bits((uint32_t)parsed_value);
    free(input);

    if (printf("%" PRIu32 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}