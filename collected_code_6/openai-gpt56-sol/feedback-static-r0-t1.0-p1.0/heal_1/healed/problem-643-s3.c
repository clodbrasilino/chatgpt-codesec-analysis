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

    for (size_t i = 1U; i + 1U < length; ++i) {
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
    bool too_long = false;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U < sizeof word) {
            word[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (too_long) {
        return 1;
    }

    if (length > 0U && word[length - 1U] == '\r') {
        --length;
    }

    word[length] = '\0';

    printf("%s\n", matches_word(word, length) ? "match" : "no match");
    return 0;
}