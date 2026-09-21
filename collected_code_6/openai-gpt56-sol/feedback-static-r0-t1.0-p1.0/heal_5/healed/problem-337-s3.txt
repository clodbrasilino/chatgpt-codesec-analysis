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
    size_t end;

    if (string == NULL || word == NULL || word_length == 0U) {
        return false;
    }

    end = string_length;

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
    const char *string;
    const char *word;
    size_t string_length;
    size_t word_length;
    bool matched;

    if (argc != 3 || argv == NULL) {
        fprintf(stderr, "Usage: %s <string> <word>\n",
                argv != NULL && argc > 0 && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return 2;
    }

    string = argv[1];
    word = argv[2];

    if (string == NULL || word == NULL) {
        fputs("Invalid null argument\n", stderr);
        return 2;
    }

    string_length = strnlen(string, SIZE_MAX);
    word_length = strnlen(word, SIZE_MAX);

    matched = matches_word_at_end(string, string_length, word, word_length);

    puts(matched ? "match" : "no match");
    return matched ? 0 : 1;
}