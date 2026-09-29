#include <stdio.h>
#include <string.h>

int match_word_at_start(const char *str, const char *word) {
    size_t str_len = 0;
    size_t word_len = 0;

    while (str[str_len] != '\0' && str[str_len] == word[word_len]) {
        str_len++;
        word_len++;
    }

    if (word[word_len] != '\0') return 0;

    if (str[str_len] == '\0' || str[str_len] == ' ') return 1;
    return 0;
}

int main() {
    const char *test_str = "example string";
    const char *word1 = "example";
    const char *word2 = "test";

    if (match_word_at_start(test_str, word1)) {
        printf("Match found: %s\n", word1);
    } else {
        printf("No match: %s\n", word1);
    }

    if (match_word_at_start(test_str, word2)) {
        printf("Match found: %s\n", word2);
    } else {
        printf("No match: %s\n", word2);
    }

    return 0;
}