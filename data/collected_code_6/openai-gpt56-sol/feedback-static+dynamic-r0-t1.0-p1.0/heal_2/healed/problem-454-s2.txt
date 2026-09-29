#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length == SIZE_MAX - 1) {
            free(word);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 64 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *resized = realloc(word, new_capacity);
            if (resized == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(word);
        return EXIT_SUCCESS;
    }

    if (capacity <= length) {
        char *resized = realloc(word, length + 1);
        if (resized == NULL) {
            free(word);
            return EXIT_FAILURE;
        }

        word = resized;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    free(word);
    return EXIT_SUCCESS;
}