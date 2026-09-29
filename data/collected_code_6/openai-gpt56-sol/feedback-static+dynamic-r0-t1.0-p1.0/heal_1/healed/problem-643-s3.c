#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool matches_word(const char *word, size_t length)
{
    if (word == NULL || length < 3U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isalpha((unsigned char)word[i])) {
            return false;
        }
    }

    for (size_t i = 1U; i < length - 1U; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    bool line_complete = false;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            line_complete = true;
            break;
        }

        if (length + 1U >= sizeof word) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }

        word[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0U) {
        return 0;
    }

    if (!line_complete && ch != EOF) {
        return 1;
    }

    if (length > 0U && word[length - 1U] == '\r') {
        --length;
    }

    word[length] = '\0';

    if (printf("%s\n", matches_word(word, length) ? "match" : "no match") < 0) {
        return 1;
    }

    return 0;
}