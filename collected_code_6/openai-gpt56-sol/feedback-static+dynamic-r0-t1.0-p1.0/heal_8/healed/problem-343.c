#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    size_t capacity = 128;
    size_t length = 0;
    size_t digits;
    size_t letters;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int character;

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too large.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        input[length++] = (char)(unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    input[length] = '\0';

    if (count_digits_and_letters(input, &digits, &letters) != 0) {
        fputs("Invalid argument.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}