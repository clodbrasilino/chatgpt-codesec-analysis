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
    size_t capacity = 64;
    size_t length = 0;
    char *word = malloc(capacity);

    if (word == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(word + length, (int)(capacity - length), stdin) != NULL) {
        size_t added = strcspn(word + length, "\r\n");
        length += added;

        if (word[length] == '\r' || word[length] == '\n') {
            word[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            free(word);
            return EXIT_FAILURE;
        }

        size_t new_capacity = capacity * 2;

        if (new_capacity > (size_t)INT32_MAX) {
            free(word);
            return EXIT_FAILURE;
        }

        char *new_word = realloc(word, new_capacity);
        if (new_word == NULL) {
            free(word);
            return EXIT_FAILURE;
        }

        word = new_word;
        capacity = new_capacity;
    }

    if (ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    word[length] = '\0';

    int result = puts(contains_z(word) ? "match" : "no match");
    free(word);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}