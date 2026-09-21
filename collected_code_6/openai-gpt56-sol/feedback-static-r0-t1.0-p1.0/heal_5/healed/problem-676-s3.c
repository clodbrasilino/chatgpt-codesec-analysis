#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_non_alphanumeric(char *string)
{
    unsigned char *source;
    char *destination;

    if (string == NULL) {
        return -1;
    }

    source = (unsigned char *)string;
    destination = string;

    while (*source != '\0') {
        if (isalnum((int)*source) != 0) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
    return 0;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }

            if (character == EOF && length == 0) {
                free(input);
                return EXIT_SUCCESS;
            }

            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    input[length] = '\0';

    if (remove_non_alphanumeric(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}