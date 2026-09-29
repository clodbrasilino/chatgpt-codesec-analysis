#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int move_numbers_to_end(char *str, size_t capacity)
{
    size_t length = 0;
    size_t write_index = 0;
    char *result;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    while (length < capacity && str[length] != '\0') {
        ++length;
    }

    if (length == capacity) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    result[write_index] = '\0';

    for (size_t i = 0; i <= length; ++i) {
        str[i] = result[i];
    }

    free(result);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = length + 1;
    }

    input[length] = '\0';

    if (move_numbers_to_end(input, capacity) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}