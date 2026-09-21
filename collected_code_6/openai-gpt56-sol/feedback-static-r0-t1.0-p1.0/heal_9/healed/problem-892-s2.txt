#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_multiple_spaces(char *str, size_t length)
{
    size_t read_pos;
    size_t write_pos = 0;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    for (read_pos = 0; read_pos < length; ++read_pos) {
        unsigned char current = (unsigned char)str[read_pos];

        if (current != (unsigned char)' ' || !previous_was_space) {
            str[write_pos++] = (char)current;
        }

        previous_was_space = current == (unsigned char)' ';
    }

    str[write_pos] = '\0';
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || required > SIZE_MAX) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

int main(void)
{
    char *text = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_SUCCESS;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length > SIZE_MAX - 2) {
            status = EXIT_FAILURE;
            break;
        }

        if (capacity - length < 2) {
            if (!grow_buffer(&text, &capacity, length + 2)) {
                status = EXIT_FAILURE;
                break;
            }
        }

        text[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS && length > 0) {
        text[length] = '\0';
        remove_multiple_spaces(text, length);

        if (fputs(text, stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(text);
    return status;
}