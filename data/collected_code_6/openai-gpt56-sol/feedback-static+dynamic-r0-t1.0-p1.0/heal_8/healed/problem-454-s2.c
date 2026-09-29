#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char *word = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (word == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(word, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(word);
        return status;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && length > MAX_INPUT_LENGTH) {
        free(word);
        return EXIT_FAILURE;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    free(word);
    return EXIT_SUCCESS;
}