#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int toggle_case(char *str)
{
    if (str == NULL) {
        return -1;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str;

        if (islower(ch)) {
            *str = (char)toupper(ch);
        } else if (isupper(ch)) {
            *str = (char)tolower(ch);
        }

        ++str;
    }

    return 0;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                fputs("Input is too large\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                fputs("Memory allocation failed\n", stderr);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    buffer[length] = '\0';

    if (toggle_case(buffer) != 0) {
        free(buffer);
        fputs("Invalid string\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(buffer, stdout) == EOF) {
        free(buffer);
        perror("fputs");
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}