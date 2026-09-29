#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 256

bool is_word_length_odd(const char *word, size_t max_length)
{
    size_t length;

    if (word == NULL) {
        return false;
    }

    length = strnlen(word, max_length);
    return (length % 2U) != 0U;
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
    char buffer[MAX_WORD_LENGTH];
    size_t length;

    printf("Enter a word: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    length = strnlen(buffer, sizeof(buffer));
    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
    } else if (length == sizeof(buffer) - 1U) {
        discard_remaining_input();
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Error: empty input.\n");
        return 1;
    }

    if (is_word_length_odd(buffer, sizeof(buffer))) {
        printf("The length of the word \"%s\" is odd.\n", buffer);
    } else {
        printf("The length of the word \"%s\" is even.\n", buffer);
    }

    return 0;
}