#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

bool is_word_length_even(const char *word)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strlen(word);
    return (len % 2U) == 0U;
}

int main(void)
{
    char buffer[MAX_WORD_LEN];
    char *newline = NULL;

    printf("Enter a word: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "No word entered.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer)) {
        printf("The word \"%s\" has an even length.\n", buffer);
    } else {
        printf("The word \"%s\" has an odd length.\n", buffer);
    }

    return EXIT_SUCCESS;
}