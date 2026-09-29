#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0 &&
           isdigit((unsigned char)str[length - 1]) != 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *data;
    int ch = EOF;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(data);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(data);
                return -1;
            }

            break;
        }

        if (used >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(data);
        return -1;
    }

    if (used == 0) {
        free(data);
        return ch == EOF ? 0 : 1;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int status = read_line(stdin, &input, &length);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (puts(ends_with_number(input, length) ? "true" : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}