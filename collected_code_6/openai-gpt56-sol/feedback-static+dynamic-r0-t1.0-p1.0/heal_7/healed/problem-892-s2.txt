#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_multiple_spaces(char *str, size_t length)
{
    size_t read_index;
    size_t write_index = 0;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        unsigned char current = (unsigned char)str[read_index];

        if (current != (unsigned char)' ' || !previous_was_space) {
            str[write_index++] = (char)current;
        }

        previous_was_space = current == (unsigned char)' ';
    }

    str[write_index] = '\0';
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 128;
    char *text;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    text = malloc(capacity);
    if (text == NULL) {
        return -1;
    }

    *length = 0;

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(text);
                return -1;
            }
            break;
        }

        if (*length >= capacity - 1) {
            size_t required;
            size_t new_capacity;
            char *new_text;

            if (*length > SIZE_MAX - 2) {
                free(text);
                return -1;
            }

            required = *length + 2;

            if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_text = realloc(text, new_capacity);
            if (new_text == NULL) {
                free(text);
                return -1;
            }

            text = new_text;
            capacity = new_capacity;
        }

        text[(*length)++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    text[*length] = '\0';
    *buffer = text;
    return 0;
}

int main(void)
{
    char *text = NULL;
    size_t length = 0;

    if (read_line(stdin, &text, &length) != 0) {
        return EXIT_FAILURE;
    }

    remove_multiple_spaces(text, length);

    if (fputs(text, stdout) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}