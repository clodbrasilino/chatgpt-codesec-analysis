#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word(const char *word)
{
    size_t length;

    if (word == NULL) {
        return false;
    }

    length = strlen(word);
    if (length < 3U) {
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
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    size_t length = strlen(word);
    if (length > 0U && word[length - 1U] == '\n') {
        word[--length] = '\0';
        if (length > 0U && word[length - 1U] == '\r') {
            word[length - 1U] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        return 1;
    }

    printf("%s\n", matches_word(word) ? "match" : "no match");
    return 0;
}