#include <stdio.h>
#include <stdlib.h>

static void remove_odd_characters(char *string)
{
    size_t read_index = 0;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];
        if (string[read_index + 1] == '\0') {
            break;
        }
        read_index += 2;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *resized_string;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            resized_string = realloc(string, new_capacity);
            if (resized_string == NULL) {
                free(string);
                return 1;
            }

            string = resized_string;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(string);
        return 1;
    }

    if (character == EOF && length == 0) {
        free(string);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *resized_string = realloc(string, new_capacity);

        if (resized_string == NULL) {
            free(string);
            return 1;
        }

        string = resized_string;
        capacity = new_capacity;
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