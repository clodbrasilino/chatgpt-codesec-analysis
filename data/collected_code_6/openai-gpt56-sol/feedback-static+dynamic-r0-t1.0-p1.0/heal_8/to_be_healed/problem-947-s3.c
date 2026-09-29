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
            if (current == SIZE_MAX) {
                return 0;
            }
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
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 256;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
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