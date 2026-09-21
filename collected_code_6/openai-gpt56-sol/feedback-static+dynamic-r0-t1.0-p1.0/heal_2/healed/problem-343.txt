#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int count_digits_and_letters(const char *string, size_t *digits, size_t *letters)
{
    const unsigned char *current;

    if (string == NULL || digits == NULL || letters == NULL) {
        return -1;
    }

    *digits = 0;
    *letters = 0;

    for (current = (const unsigned char *)string; *current != '\0'; ++current) {
        if (isdigit(*current)) {
            ++*digits;
        } else if (isalpha(*current)) {
            ++*letters;
        }
    }

    return 0;
}

int main(void)
{
    char *input;
    size_t capacity = 128;
    size_t length = 0;
    size_t digits;
    size_t letters;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (count_digits_and_letters(input, &digits, &letters) != 0) {
        free(input);
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}