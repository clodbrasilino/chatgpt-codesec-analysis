#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool is_optional_punctuation(unsigned char ch)
{
    return ispunct(ch) != 0;
}

static bool matches_word_at_end(const char *string, size_t string_length,
                                const char *word, size_t word_length)
{
    size_t end = string_length;

    if (string == NULL || word == NULL || word_length == 0U) {
        return false;
    }

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
    bool matched;
    size_t string_length;
    size_t word_length;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <word>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 2;
    }

    string_length = strlen(argv[1]);
    word_length = strlen(argv[2]);

    matched = matches_word_at_end(argv[1], string_length, argv[2], word_length);
    puts(matched ? "match" : "no match");

    return matched ? 0 : 1;
}