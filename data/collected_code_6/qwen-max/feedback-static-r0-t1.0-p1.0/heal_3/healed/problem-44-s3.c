#include <stdio.h>
#include <string.h>

int match_word_at_beginning(const char *str, const char *word) {
    size_t word_len = strlen(word);
    if (str == NULL || word == NULL || *str == '\0' || *word == '\0') {
        return 0;
    }
    for (size_t i = 0; i < word_len; ++i) {
        if (str[i] != word[i]) {
            return 0;
        }
        if (str[i] == '\0') {
            return 0;
        }
    }
    if (str[word_len] == ' ' || str[word_len] == '\0') {
        return 1;
    }
    return 0;
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