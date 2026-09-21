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

int main(void)
{
    char *text = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_SUCCESS;

    for (;;) {
        int ch;

        if (length > SIZE_MAX - 2) {
            status = EXIT_FAILURE;
            break;
        }

        if (length + 2 > capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_text = realloc(text, new_capacity);

            if (new_text == NULL) {
                status = EXIT_FAILURE;
                break;
            }

            text = new_text;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                status = EXIT_FAILURE;
            }
            break;
        }

        text[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
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