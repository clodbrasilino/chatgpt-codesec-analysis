#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool is_optional_punctuation(unsigned char ch)
{
    return ispunct(ch) != 0;
}

static bool matches_word_at_end(const char *string, const char *word)
{
    size_t end;
    size_t word_length;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    end = strlen(string);
    word_length = strlen(word);

    while (end > 0U &&
           is_optional_punctuation((unsigned char)string[end - 1U])) {
        --end;
    }

    if (end < word_length) {
        return false;
    }

    if (memcmp(string + end - word_length, word, word_length) != 0) {
        return false;
    }

    return end == word_length ||
           isspace((unsigned char)string[end - word_length - 1U]) != 0;
}

int main(int argc, char *const argv[])
{
    const char *const string = argv[1];
    const char *const word = argv[2];
    bool matched;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <word>\n", argv[0]);
        return 2;
    }

    matched = matches_word_at_end(string, word);
    puts(matched ? "match" : "no match");

    return matched ? 0 : 1;
}