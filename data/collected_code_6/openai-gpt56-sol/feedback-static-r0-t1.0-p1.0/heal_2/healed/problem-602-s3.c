#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_repeated_character(const char *string, size_t length,
                             unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (seen[character] != 0U) {
            *result = character;
            return 1;
        }

        seen[character] = 1U;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    fprintf(stderr, "Input is too large.\n");
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    unsigned char repeated_character = 0U;
    int status = first_repeated_character(
        input != NULL ? input : "",
        length,
        &repeated_character
    );

    free(input);

    if (status < 0) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    if (status == 1) {
        if (printf("%c\n", (int)repeated_character) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated character found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}