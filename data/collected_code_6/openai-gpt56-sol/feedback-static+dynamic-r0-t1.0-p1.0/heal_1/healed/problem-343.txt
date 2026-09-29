#include <ctype.h>
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
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t digits;
    size_t letters;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return 1;
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
        return 1;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }

        input = new_input;
        capacity = length + 1;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }
    }

    input[length] = '\0';

    if (count_digits_and_letters(input, &digits, &letters) != 0) {
        free(input);
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    free(input);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return 1;
    }

    return 0;
}