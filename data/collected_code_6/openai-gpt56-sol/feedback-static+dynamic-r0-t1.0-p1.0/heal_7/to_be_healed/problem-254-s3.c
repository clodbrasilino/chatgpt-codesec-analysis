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

        while (*p != '\0' && !isalpha(*p)) {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        start = p;

        while (*p != '\0' && isalpha(*p)) {
            ++p;
        }

        length = (size_t)(p - start);

        if (tolower(start[0]) == 'a' || tolower(start[0]) == 'e') {
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
        size_t available;

        if (length >= capacity) {
            free(line);
            return -1;
        }

        available = capacity - length;

        if (fgets(line + length, available > (size_t)INT_MAX
                                      ? INT_MAX
                                      : (int)available,
                  stream) == NULL) {
            if (ferror(stream)) {
                free(line);
                return -1;
            }

            if (length == 0) {
                line[0] = '\0';
            }
            break;
        }

        while (length < capacity && line[length] != '\0' &&
               line[length] != '\n') {
            ++length;
        }

        if (length < capacity && line[length] == '\n') {
            /* Possible weaknesses found:
             *  line[length] is assigned
             */
            line[length] = '\0';
            break;
        }

        if (feof(stream)) {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(line);
            return -1;
        }

        {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
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
    }

    /* Possible weaknesses found:
     *  line[length] is overwritten
     *  Variable 'line[length]' is reassigned a value before the old one has been used. [redundantAssignment]
     */
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