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
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        char *new_word;
        size_t required;
        size_t new_capacity;

        if (ch == '\n' || ch == '\r') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(word);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (capacity < required) {
            new_capacity = capacity != 0 ? capacity : 64;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            new_word = realloc(word, new_capacity);
            if (new_word == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (word == NULL) {
        word = malloc(1);
        if (word == NULL) {
            return EXIT_FAILURE;
        }
    }

    word[length] = '\0';

    if (puts(contains_z(word) ? "match" : "no match") == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}