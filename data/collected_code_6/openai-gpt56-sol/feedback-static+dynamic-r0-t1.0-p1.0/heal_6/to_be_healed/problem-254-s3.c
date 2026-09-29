#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_matching_words(const char *text)
{
    const unsigned char *p;

    if (text == NULL) {
        return -1;
    }

    p = (const unsigned char *)text;

    while (*p != '\0') {
        const unsigned char *start;
        size_t length;

        while (*p != '\0' && !isalpha((unsigned char)*p)) {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        start = p;

        while (*p != '\0' && isalpha((unsigned char)*p)) {
            ++p;
        }

        length = (size_t)(p - start);

        if (tolower((unsigned char)start[0]) == 'a' ||
            tolower((unsigned char)start[0]) == 'e') {
            if (length > (size_t)INT_MAX) {
                return -1;
            }

            if (printf("%.*s\n", (int)length, (const char *)start) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;

    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream)) {
                free(line);
                return -1;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = length + 2;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < length + 2) {
                    new_capacity = length + 2;
                }
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    line[length] = '\0';
    *buffer = line;

    return 0;
}

int main(void)
{
    char *line = NULL;
    int status = EXIT_SUCCESS;

    if (read_line(stdin, &line) != 0) {
        return EXIT_FAILURE;
    }

    if (print_matching_words(line) != 0) {
        status = EXIT_FAILURE;
    }

    free(line);
    return status;
}