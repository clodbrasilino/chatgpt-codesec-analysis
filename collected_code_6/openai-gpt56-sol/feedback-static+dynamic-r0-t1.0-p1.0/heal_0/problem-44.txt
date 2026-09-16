#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_start(const char *string, const char *word)
{
    size_t word_length;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    word_length = strlen(word);

    if (strncmp(string, word, word_length) != 0) {
        return false;
    }

    return string[word_length] == '\0' ||
           string[word_length] == ' ' ||
           string[word_length] == '\t' ||
           string[word_length] == '\n' ||
           string[word_length] == '\r' ||
           string[word_length] == '\f' ||
           string[word_length] == '\v';
}

int main(void)
{
    const char *string = "example string";
    const char *word = "example";

    if (matches_word_at_start(string, word)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}