#include <stdio.h>
#include <string.h>

int is_concatenation(const char *str, const char *word) {
    size_t word_len = strlen(word);
    size_t str_len = strlen(str);

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

    if (is_concatenation(test_str, test_word)) {
        printf("The string is a concatenation of the word.\n");
    } else {
        printf("The string is not a concatenation of the word.\n");
    }

    return 0;
}