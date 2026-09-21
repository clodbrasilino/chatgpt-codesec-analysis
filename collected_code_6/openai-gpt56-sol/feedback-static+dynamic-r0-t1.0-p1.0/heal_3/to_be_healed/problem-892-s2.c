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

        if (current != ' ' || !previous_was_space) {
            str[write_index++] = (char)current;
        }

        previous_was_space = (current == ' ');
    }

    str[write_index] = '\0';
}

int main(void)
{
    char *text = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (length == SIZE_MAX - 1) {
            free(text);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_text;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_text = realloc(text, new_capacity);
            if (new_text == NULL) {
                free(text);
                return EXIT_FAILURE;
            }

            text = new_text;
            capacity = new_capacity;
        }

        text[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(text);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(text);
        return EXIT_SUCCESS;
    }

    text[length] = '\0';
    remove_multiple_spaces(text, length);

    if (fputs(text, stdout) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}