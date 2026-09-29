#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *word = malloc((size_t)MAX_INPUT_LENGTH + 2);

    if (word == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(word, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            free(word);
            return EXIT_FAILURE;
        }

        word[0] = '\0';
    } else {
        size_t length = strcspn(word, "\r\n");

        if (word[length] == '\0' && length > MAX_INPUT_LENGTH) {
            free(word);
            return EXIT_FAILURE;
        }

        word[length] = '\0';
    }

    puts(contains_z(word) ? "Match" : "No match");

    free(word);
    return EXIT_SUCCESS;
}