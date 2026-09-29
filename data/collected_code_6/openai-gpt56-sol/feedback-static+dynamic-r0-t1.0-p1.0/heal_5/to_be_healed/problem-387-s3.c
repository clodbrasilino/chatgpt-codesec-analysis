#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'end>begin' is not redundant
     */
    while (end > begin && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    /* Possible weaknesses found:
     *  Condition 'end-begin>=2' is always false [knownConditionTrueFalse]
     *  Condition 'end-begin>=2' is always false
     */
    if (end - begin >= 2 &&
        hex[begin] == '0' &&
        (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
        begin += 2;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1];
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e' || last == 'A' ||
               last == 'C' || last == 'E';

    return 1;
}

static int read_line(char **buffer, size_t *length)
{
    char *line;
    size_t capacity = 128;
    size_t used = 0;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[used++] = (char)ch;
    }

    if (used > 0 && line[used - 1] == '\r') {
        --used;
    }

    *buffer = line;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int is_even;

    if (!read_line(&input, &length)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_hex_even(input, length, &is_even)) {
        free(input);
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_even ? "Even" : "Odd");

    return EXIT_SUCCESS;
}