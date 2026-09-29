#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t shortest_word_length(const char *text)
{
    size_t shortest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text)) {
            if (current != 0 && (shortest == 0 || current < shortest)) {
                shortest = current;
            }
            current = 0;
        } else {
            ++current;
        }
        ++text;
    }

    if (current != 0 && (shortest == 0 || current < shortest)) {
        shortest = current;
    }

    return shortest;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *resized;

        if (new_capacity <= capacity) {
            free(input);
            return 1;
        }

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            return 1;
        }

        input = resized;
    }

    input[length] = '\0';
    printf("%zu\n", shortest_word_length(input));

    free(input);
    return 0;
}