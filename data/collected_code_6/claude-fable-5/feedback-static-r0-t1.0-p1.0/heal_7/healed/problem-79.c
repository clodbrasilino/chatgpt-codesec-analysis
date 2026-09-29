#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_WORD_LENGTH 256U

static size_t safe_strnlen(const char *str, size_t max_length)
{
    size_t length = 0U;

    if (str == NULL) {
        return 0U;
    }

    while (length < max_length && str[length] != '\0') {
        length++;
    }

    return length;
}

bool is_word_length_odd(const char *word, size_t max_length)
{
    size_t length;

    if (word == NULL) {
        return false;
    }

    length = safe_strnlen(word, max_length);
    return (length % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < (size_t)MAX_WORD_LENGTH * 1024U);
}

int main(void)
{
    char buffer[MAX_WORD_LENGTH];
    size_t length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a word: ");
    (void)fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    length = safe_strnlen(buffer, sizeof(buffer));

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        length--;
    } else if (length == sizeof(buffer) - 1U) {
        discard_remaining_input();
    }

    if (length == 0U || buffer[0] == '\0') {
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