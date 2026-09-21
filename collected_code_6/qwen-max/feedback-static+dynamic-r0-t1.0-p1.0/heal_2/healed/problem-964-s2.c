#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word, size_t word_len) {
    if (word == NULL || word_len == 0) {
        return false;
    }
    return (word_len % 2) == 0;
}

int main() {
    const char *test_word1 = "even";
    const char *test_word2 = "odd";

    size_t len1 = 0;
    while (test_word1[len1] != '\0') {
        len1++;
    }

    size_t len2 = 0;
    while (test_word2[len2] != '\0') {
        len2++;
    }

    printf("%s: %s\n", test_word1, is_length_even(test_word1, len1) ? "Even" : "Odd");
    printf("%s: %s\n", test_word2, is_length_even(test_word2, len2) ? "Even" : "Odd");

    return 0;
}