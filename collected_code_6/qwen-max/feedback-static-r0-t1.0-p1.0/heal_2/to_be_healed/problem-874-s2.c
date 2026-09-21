#include <stdio.h>
#include <string.h>

int is_concatenation(const char *str, const char *word, size_t str_len, size_t word_len) {
    if (str_len % word_len != 0) {
        return 0;
    }

    for (size_t i = 0; i < str_len; i += word_len) {
        if (strncmp(str + i, word, word_len) != 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    const char *test_str = "abcabcabc";
    const char *test_word = "abc";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test_str_len = strlen(test_str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test_word_len = strlen(test_word);

    if (is_concatenation(test_str, test_word, test_str_len, test_word_len)) {
        printf("The string is a concatenation of the word.\n");
    } else {
        printf("The string is not a concatenation of the word.\n");
    }

    return 0;
}