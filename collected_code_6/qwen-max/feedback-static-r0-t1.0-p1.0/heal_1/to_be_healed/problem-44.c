#include <stdio.h>
#include <string.h>

int match_word_at_start(const char *str, const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);

    if (str_len < word_len) return 0;

    for (size_t i = 0; i < word_len; ++i) {
        if (str[i] != word[i]) return 0;
    }

    if (str[word_len] == '\0' || str[word_len] == ' ') return 1;
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