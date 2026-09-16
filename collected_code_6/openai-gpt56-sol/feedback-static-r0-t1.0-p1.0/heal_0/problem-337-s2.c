#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_end(const char *string, const char *word)
{
    size_t string_length;
    size_t word_length;
    size_t end;

    if (string == NULL || word == NULL || *word == '\0') {
        return false;
    }

    string_length = strlen(string);
    word_length = strlen(word);
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
           !isalnum((unsigned char)string[end - word_length - 1U]);
}

int main(void)
{
    const char *text = "The final word is example!";
    const char *word = "example";

    if (matches_word_at_end(text, word)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}