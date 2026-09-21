#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscores(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *current = (unsigned char *)string;
         *current != '\0';
         ++current) {
        if (*current == '_') {
            *current = ' ';
        } else if (*current == ' ' || *current == '\t' ||
                   *current == '\n' || *current == '\r' ||
                   *current == '\f' || *current == '\v') {
            *current = '_';
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

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fprintf(stderr, "Unable to allocate memory.\n");
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fprintf(stderr, "Unable to allocate memory.\n");
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        free(input);
        fprintf(stderr, "Unable to process the input.\n");
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