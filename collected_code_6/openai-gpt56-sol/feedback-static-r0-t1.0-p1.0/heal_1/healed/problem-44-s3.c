#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool starts_with_word(const char *string, size_t string_length,
                             const char *word, size_t word_length)
{
    size_t i;

    if (string == NULL || word == NULL || word_length == 0 ||
        string_length < word_length) {
        return false;
    }

    for (i = 0; i < word_length; ++i) {
        if (string[i] != word[i]) {
            return false;
        }
    }

    if (string_length == word_length) {
        return true;
    }

    switch (string[word_length]) {
    case ' ':
    case '\t':
    case '\n':
    case '\r':
    case '\f':
    case '\v':
        return true;
    default:
        return false;
    }
}

int main(void)
{
    static const char string[] = "example text";
    static const char word[] = "example";

    if (starts_with_word(string, sizeof(string) - 1,
                         word, sizeof(word) - 1)) {
        if (puts("Match") == EOF) {
            return 1;
        }
    } else {
        if (puts("No match") == EOF) {
            return 1;
        }
    }

    return 0;
}