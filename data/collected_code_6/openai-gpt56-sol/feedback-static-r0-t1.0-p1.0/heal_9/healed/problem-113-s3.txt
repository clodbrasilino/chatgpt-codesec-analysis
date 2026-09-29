#include <ctype.h>
#include <limits.h>
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
    size_t length = 0;
    size_t capacity = 128;
    char *line;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    line[0] = '\0';

    for (;;) {
        size_t available;
        char *result;
        char *terminator;
        size_t chunk_length;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2 ||
                capacity * 2 > (size_t)INT_MAX) {
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

        available = capacity - length;
        result = fgets(line + length, (int)available, stream);

        if (result == NULL) {
            if (ferror(stream) || length == 0) {
                free(line);
                return NULL;
            }

            line[length] = '\0';
            return line;
        }

        terminator = memchr(line + length, '\0', available);
        if (terminator == NULL) {
            free(line);
            return NULL;
        }

        chunk_length = (size_t)(terminator - (line + length));
        length += chunk_length;

        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';

            if (length > 0 && line[length - 1] == '\r') {
                line[--length] = '\0';
            }

            return line;
        }

        if (feof(stream)) {
            return line;
        }
    }
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