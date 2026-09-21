#include <stdio.h>
#include <string.h>

int match_word_at_beginning(const char *str, const char *word) {
    size_t str_len = strnlen(str, 1024);
    size_t word_len = strnlen(word, 1024);

    if (word_len > 0 && str_len >= word_len && strncmp(str, word, word_len) == 0 && (str[word_len] == ' ' || str[word_len] == '\0')) {
        return 1;
    }
    return 0;
}

int main() {
    const char *test_str = "hello world";
    const char *word = "hello";

    if (match_word_at_beginning(test_str, word)) {
        printf("Match found at the beginning of the string.\n");
    } else {
        printf("No match found at the beginning of the string.\n");
    }

    return 0;
}