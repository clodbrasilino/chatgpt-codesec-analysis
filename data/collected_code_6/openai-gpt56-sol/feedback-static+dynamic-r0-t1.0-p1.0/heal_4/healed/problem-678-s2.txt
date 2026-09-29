#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_spaces(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    size_t length = 0;
    size_t capacity = 128;
    char *string = malloc(capacity);

    if (string == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(string);
                return EXIT_FAILURE;
            }

            if (length == 0) {
                free(string);
                return EXIT_SUCCESS;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large.\n", stderr);
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(string);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)ch;
    }

    string[length] = '\0';
    remove_spaces(string);

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}