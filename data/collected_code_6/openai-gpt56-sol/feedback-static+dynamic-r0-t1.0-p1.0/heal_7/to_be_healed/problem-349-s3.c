#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        ++str;
    }

    return true;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(line);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (is_binary_string(input)) {
        if (fputs("Binary string\n", stdout) == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (fputs("Not a binary string\n", stdout) == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}