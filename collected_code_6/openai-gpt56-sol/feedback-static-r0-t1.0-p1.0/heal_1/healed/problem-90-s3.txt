#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t longest_word_length(const char *text)
{
    size_t longest = 0U;
    size_t current = 0U;

    if (text == NULL) {
        return 0U;
    }

    while (*text != '\0') {
        if (isalnum((unsigned char)*text) != 0) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0U;
        }
        ++text;
    }

    return longest;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) != 0) {
        free(input);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", longest_word_length(input)) < 0) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}