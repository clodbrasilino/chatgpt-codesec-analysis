#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_characters(char *string)
{
    char *read_ptr;
    char *write_ptr;

    if (string == NULL) {
        return;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        *write_ptr++ = *read_ptr++;

        if (*read_ptr != '\0') {
            ++read_ptr;
        }
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required;
        size_t new_capacity;
        char *resized;

        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (capacity < required) {
            new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(string);
        return EXIT_SUCCESS;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (capacity <= length) {
        char *resized;

        if (length == SIZE_MAX) {
            free(string);
            return EXIT_FAILURE;
        }

        resized = realloc(string, length + 1);
        if (resized == NULL) {
            free(string);
            return EXIT_FAILURE;
        }

        string = resized;
    }

    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}