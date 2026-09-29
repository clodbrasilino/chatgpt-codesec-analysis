#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        char *expanded;
        size_t new_capacity;

        if (ch == '\n' || ch == '\r') {
            break;
        }

        if (length == capacity) {
            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            expanded = realloc(input, new_capacity);
            if (expanded == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = expanded;
            capacity = new_capacity;
        }

        input[length] = (char)(unsigned char)ch;
        length++;
    }

    if (ferror(stdin) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}