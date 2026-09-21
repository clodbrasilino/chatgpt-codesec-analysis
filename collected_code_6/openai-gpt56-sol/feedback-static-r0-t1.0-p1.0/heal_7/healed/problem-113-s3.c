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

    do {
        if (!isdigit(*p)) {
            return false;
        }
        ++p;
    } while (*p != '\0');

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

    while (fgets(line + length, (int)(capacity - length), stream) != NULL) {
        length += strlen(line + length);

        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';
            return line;
        }

        if (feof(stream)) {
            return line;
        }

        if (capacity > SIZE_MAX / 2 || capacity * 2 > (size_t)INT_MAX) {
            free(line);
            return NULL;
        }

        capacity *= 2;

        char *resized = realloc(line, capacity);
        if (resized == NULL) {
            free(line);
            return NULL;
        }

        line = resized;
    }

    if (ferror(stream) || length == 0) {
        free(line);
        return NULL;
    }

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