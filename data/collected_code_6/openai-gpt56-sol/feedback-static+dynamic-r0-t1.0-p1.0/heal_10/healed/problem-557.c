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
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (;;) {
        int ch;

        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                perror("fgetc");
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            fputs("Input too large\n", stderr);
            free(buffer);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                fputs("Input too large\n", stderr);
                free(buffer);
                return EXIT_FAILURE;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                perror("realloc");
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    buffer[length] = '\0';

    if (toggle_case(buffer) != 0) {
        fputs("Invalid string\n", stderr);
        free(buffer);
        return EXIT_FAILURE;
    }

    if (fputs(buffer, stdout) == EOF) {
        perror("fputs");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}