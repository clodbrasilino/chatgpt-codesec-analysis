#include <stdio.h>
#include <string.h>

int is_word_length_even(const char *word, size_t word_len) {
    if (word == NULL || word_len == 0) {
        return 0;
    }
    return (word_len % 2 == 0) ? 1 : 0;
}

int main() {
    const char *test_word = "example";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test_word_len = strlen(test_word);
    int result = is_word_length_even(test_word, test_word_len);
    if (result) {
        printf("The word length is even.\n");
    } else {
        printf("The word length is odd.\n");
    }
    return 0;
}