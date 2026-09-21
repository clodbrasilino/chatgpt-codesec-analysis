#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int match_word_at_end(const char *str, size_t str_len, const char *word, size_t word_len) {
    if (str_len < word_len) return 0;

    const char *start = str + str_len - word_len;
    while (start > str && isspace(*(start - 1))) start--;

    if (str_len - (start - str) < word_len) return 0;

    for (size_t i = 0; i < word_len; i++) {
        if (tolower(start[i]) != tolower(word[i])) return 0;
    }

    return 1;
}

int main() {
    const char *str = "This is a sample string with the word.";
    const char *word = "word";
    size_t str_len = strnlen(str, INT_MAX);
    size_t word_len = strnlen(word, INT_MAX);

    if (match_word_at_end(str, str_len, word, word_len)) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }
    return 0;
}