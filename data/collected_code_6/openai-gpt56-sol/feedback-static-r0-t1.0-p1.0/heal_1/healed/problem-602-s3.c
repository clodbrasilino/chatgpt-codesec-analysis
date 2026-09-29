#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int first_repeated_character(const char *string, size_t length,
                             unsigned char *result)
{
    unsigned char *seen = calloc((size_t)UCHAR_MAX + 1U, sizeof(*seen));

    if (string == NULL || result == NULL) {
        free(seen);
        return -1;
    }

    if (seen == NULL) {
        return -2;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (seen[character] != 0U) {
            *result = character;
            free(seen);
            return 1;
        }

        seen[character] = 1U;
    }

    free(seen);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity <= capacity ||
                new_capacity > SIZE_MAX / sizeof(*input)) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return 1;
            }

            char *new_input = realloc(input, new_capacity * sizeof(*input));

            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
    }

    unsigned char repeated_character;
    int status = first_repeated_character(input, length, &repeated_character);

    free(input);

    if (status == -1) {
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    if (status == -2) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    if (status == 1) {
        printf("%c\n", (int)repeated_character);
    } else {
        printf("No repeated character found.\n");
    }

    return 0;
}