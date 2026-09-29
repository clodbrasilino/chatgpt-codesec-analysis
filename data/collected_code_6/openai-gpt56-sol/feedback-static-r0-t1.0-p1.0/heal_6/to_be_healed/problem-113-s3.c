#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_integer(const char *str)
{
    const unsigned char *p;

    if (str == NULL || *str == '\0') {
        return false;
    }

    p = (const unsigned char *)str;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (*p == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (!isdigit(*p)) {
            return false;
        }
        ++p;
    }

    return true;
}

static char *read_line(FILE *stream)
{
    char *line;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *input;
    int status;

    input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = printf("%s\n", is_integer(input) ? "true" : "false") < 0
                 ? EXIT_FAILURE
                 : EXIT_SUCCESS;

    free(input);
    return status;
}