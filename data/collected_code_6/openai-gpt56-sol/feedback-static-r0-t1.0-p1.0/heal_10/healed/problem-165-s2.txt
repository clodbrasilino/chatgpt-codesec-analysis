#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (tolower(ch) == 'a' + (int)i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (capacity > SIZE_MAX / 2 || new_capacity <= length) {
                free(input);
                return EXIT_FAILURE;
            }

            char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *temporary = realloc(input, length + 1);
        if (temporary == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = temporary;
        capacity = length + 1;
    }

    input[length] = '\0';

    size_t result = count_matching_positions(input);

    free(input);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}