#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static int print_binary(unsigned long long value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(value) * CHAR_BIT + 1U];
    size_t position = sizeof(binary) - 1U;

    binary[position] = '\0';

    do {
        binary[--position] = (char)('0' + (value & 1ULL));
        value >>= 1U;
    } while (value != 0ULL);

    if (fputs(&binary[position], stdout) == EOF) {
        return -1;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

static int read_line(char **line)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;

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
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long value;
    int result;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    result = print_binary(value);
    free(input);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}