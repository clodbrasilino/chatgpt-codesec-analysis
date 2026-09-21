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
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                perror("realloc");
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

    if (ferror(stdin)) {
        free(buffer);
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (buffer == NULL) {
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