#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_vowels(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        int ch = tolower((unsigned char)*str);

        if (ch == 'a' || ch == 'e' || ch == 'i' ||
            ch == 'o' || ch == 'u') {
            ++count;
        }

        ++str;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return 1;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
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

    if (ch == EOF && length == 0) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_vowels(input)) < 0) {
        free(input);
        return 1;
    }

    free(input);

    if (ferror(stdout)) {
        return 1;
    }

    return 0;
}