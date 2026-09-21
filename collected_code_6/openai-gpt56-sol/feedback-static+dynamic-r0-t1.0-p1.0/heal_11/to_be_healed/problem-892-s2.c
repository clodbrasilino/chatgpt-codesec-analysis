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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 1 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *text;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    text = malloc(capacity);
    if (text == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(text);
                return -1;
            }
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(text);
            return -1;
        }

        if (grow_buffer(&text, &capacity, used + 2) != 0) {
            free(text);
            return -1;
        }

        text[used++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    text[used] = '\0';
    *buffer = text;
    *length = used;
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