#include <stdio.h>
#include <string.h>

int match_word_at_beginning(const char *str, const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (str_len < word_len || str[word_len] != '\0' && str[word_len] != ' ') {
        return 0;
    }
    for (size_t i = 0; i < word_len; ++i) {
        if (str[i] != word[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    const char *test_str = "hello world";
    const char *test_word = "hello";
    if (match_word_at_beginning(test_str, test_word)) {
        printf("Match found at the beginning of the string.\n");
    } else {
        printf("No match found at the beginning of the string.\n");
    }
    return 0;
}