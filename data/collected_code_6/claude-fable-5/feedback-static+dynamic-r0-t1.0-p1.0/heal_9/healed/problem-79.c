#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 256

static size_t bounded_length(const char *str, size_t max_length)
{
    size_t i;

    if (str == NULL) {
        return 0U;
    }

    for (i = 0U; i < max_length; i++) {
        if (str[i] == '\0') {
            break;
        }
    }
    return i;
}

bool is_word_length_odd(const char *word, size_t max_length)
{
    size_t length;

    if (word == NULL || max_length == 0U) {
        return false;
    }

    length = bounded_length(word, max_length);
    return (length % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[MAX_WORD_LENGTH];
    size_t length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a word: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: failed to flush output.\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    length = bounded_length(buffer, sizeof(buffer));
    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
    } else if (length == sizeof(buffer) - 1U) {
        discard_remaining_input();
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Error: empty input.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_odd(buffer, sizeof(buffer))) {
        printf("The length of the word \"%s\" is odd.\n", buffer);
    } else {
        printf("The length of the word \"%s\" is even.\n", buffer);
    }

    return EXIT_SUCCESS;
}