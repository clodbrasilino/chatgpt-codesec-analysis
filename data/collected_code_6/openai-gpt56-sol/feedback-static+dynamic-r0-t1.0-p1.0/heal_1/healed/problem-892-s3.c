#include <stdio.h>
#include <stdlib.h>

static void remove_multiple_spaces(char *str)
{
    char *read_ptr = str;
    char *write_ptr = str;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ' || !previous_was_space) {
            *write_ptr++ = *read_ptr;
        }

        previous_was_space = (*read_ptr == ' ');
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return 1;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';
    remove_multiple_spaces(input);

    if (puts(input) == EOF) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}