#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t shortest_word_length(const char *text)
{
    size_t shortest = SIZE_MAX;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text)) {
            if (current != 0 && current < shortest) {
                shortest = current;
            }
            current = 0;
        } else {
            ++current;
        }
        ++text;
    }

    if (current != 0 && current < shortest) {
        shortest = current;
    }

    return shortest == SIZE_MAX ? 0 : shortest;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 256 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    size_t shortest = shortest_word_length(input);

    if (shortest == 0) {
        printf("No words found.\n");
    } else {
        printf("%zu\n", shortest);
    }

    free(input);
    return EXIT_SUCCESS;
}