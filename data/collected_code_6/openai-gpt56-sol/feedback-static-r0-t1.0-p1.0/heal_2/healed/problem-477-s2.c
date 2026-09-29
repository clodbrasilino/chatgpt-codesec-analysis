#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (unsigned char *)string;

    while (*current != '\0') {
        *current = (unsigned char)tolower(*current);
        ++current;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    if (string_to_lower(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fputs(input, stdout) == EOF) {
        perror("fputs");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}