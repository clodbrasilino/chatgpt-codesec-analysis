#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
    char buffer[256];
    size_t len;

    printf("Enter a word: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer)) {
        printf("The word \"%s\" has an even length (%zu)\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu)\n", buffer, len);
    }

    return EXIT_SUCCESS;
}