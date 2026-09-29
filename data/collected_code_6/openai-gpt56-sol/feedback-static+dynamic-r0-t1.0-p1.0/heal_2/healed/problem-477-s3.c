#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (char *p = string; *p != '\0'; ++p) {
        *p = (char)tolower((unsigned char)*p);
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;

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

            char *new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(string);
        return EXIT_SUCCESS;
    }

    string[length] = '\0';

    if (string_to_lower(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (fputs(string, stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}