#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

static bool is_word_length_odd(const char *word)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, MAX_WORD_LEN);
    return (len % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[MAX_WORD_LEN];
    size_t len;

    printf("Enter a word: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    } else if (len == sizeof(buffer) - 1U) {
        discard_remaining_input();
    }

    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_odd(buffer)) {
        printf("The word length is odd\n");
    } else {
        printf("The word length is even\n");
    }

    return EXIT_SUCCESS;
}