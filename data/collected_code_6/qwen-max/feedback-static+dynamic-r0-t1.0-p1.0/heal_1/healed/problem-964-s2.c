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
    
    printf("%s: %s\n", test_word1, is_length_even(test_word1, strlen(test_word1)) ? "Even" : "Odd");
    printf("%s: %s\n", test_word2, is_length_even(test_word2, strlen(test_word2)) ? "Even" : "Odd");

    return 0;
}