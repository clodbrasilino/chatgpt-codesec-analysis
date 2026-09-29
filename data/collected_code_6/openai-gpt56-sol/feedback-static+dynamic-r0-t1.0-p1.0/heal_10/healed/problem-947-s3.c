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
            if (current > 0 && current < shortest) {
                shortest = current;
            }
            current = 0;
        } else {
            if (current == SIZE_MAX) {
                return 0;
            }
            ++current;
        }

        ++text;
    }

    if (current > 0 && current < shortest) {
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

    while ((ch = getchar()) != EOF) {
        size_t required;

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 256 : capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        puts("No words found.");
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    {
        size_t shortest = shortest_word_length(input);

        if (shortest == 0) {
            puts("No words found.");
        } else {
            printf("%zu\n", shortest);
        }
    }

    free(input);
    return EXIT_SUCCESS;
}