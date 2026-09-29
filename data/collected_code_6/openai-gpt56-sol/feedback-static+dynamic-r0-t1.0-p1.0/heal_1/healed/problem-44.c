#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_start(const char *string, size_t string_length,
                                  const char *word, size_t word_length)
{
    if (string == NULL || word == NULL || word_length == 0 ||
        word_length > string_length) {
        return false;
    }

    if (memcmp(string, word, word_length) != 0) {
        return false;
    }

    if (word_length == string_length) {
        return true;
    }

    switch ((unsigned char)string[word_length]) {
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
    static const char string[] = "example string";
    static const char word[] = "example";

    if (matches_word_at_start(string, sizeof(string) - 1,
                              word, sizeof(word) - 1)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}