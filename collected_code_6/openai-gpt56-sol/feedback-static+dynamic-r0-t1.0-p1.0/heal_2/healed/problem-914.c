#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_two_alternating_characters(const char *string, size_t length)
{
    if (string == NULL || length < 2U || string[0] == string[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (string[i] != string[i % 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity < capacity || new_capacity > SIZE_MAX - 1U) {
                free(input);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    bool result = has_two_alternating_characters(input, length);
    free(input);

    puts(result ? "Yes" : "No");
    return EXIT_SUCCESS;
}