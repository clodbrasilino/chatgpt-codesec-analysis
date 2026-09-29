#include <stdio.h>
#include <stdlib.h>

static void remove_odd_characters(char *string)
{
    size_t read_index = 0U;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];
        read_index += 2U;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_string;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return 1;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(string);
        return 1;
    }

    if (length == 0U && character == EOF) {
        free(string);
        return 0;
    }

    if (length + 1U >= capacity) {
        char *new_string = realloc(string, length + 1U);

        if (new_string == NULL) {
            free(string);
            return 1;
        }

        string = new_string;
    }

    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return 1;
    }

    free(string);
    return 0;
}