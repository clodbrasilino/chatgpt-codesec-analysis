#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int replace_whitespace_and_underscores(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    for (current = (unsigned char *)string; *current != '\0'; ++current) {
        switch (*current) {
        case '_':
            *current = ' ';
            break;
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\f':
        case '\v':
            *current = '_';
            break;
        default:
            break;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required;
        char *resized;

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        fputs("Unable to process the input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        perror("puts");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}