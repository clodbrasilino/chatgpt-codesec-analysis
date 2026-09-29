#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_end(const char *string, size_t string_length,
                                const char *word, size_t word_length)
{
    size_t end;

    if (string == NULL || word == NULL || word_length == 0U) {
        return false;
    }

    end = string_length;

    while (end > 0U && isspace((unsigned char)string[end - 1U]) != 0) {
        --end;
    }

    while (end > 0U && ispunct((unsigned char)string[end - 1U]) != 0) {
        --end;
    }

    if (end < word_length) {
        return false;
    }

    if (memcmp(string + end - word_length, word, word_length) != 0) {
        return false;
    }

    return end == word_length ||
           isalnum((unsigned char)string[end - word_length - 1U]) == 0;
}

int main(void)
{
    static const char text[] = "The final word is example!";
    static const char word[] = "example";

    if (matches_word_at_end(text, sizeof(text) - 1U,
                            word, sizeof(word) - 1U)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}