#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int replace_whitespace_and_underscores(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *current = (unsigned char *)string;
         *current != '\0';
         ++current) {
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
        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (capacity - length < 2) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity < required) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Unable to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        perror("fgetc");
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
        free(input);
        fputs("Unable to process the input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        perror("puts");
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}