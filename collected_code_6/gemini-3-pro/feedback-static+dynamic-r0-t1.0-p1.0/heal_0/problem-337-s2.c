#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len == 0) {
        return false;
    }

    size_t end_idx = str_len;
    while (end_idx > 0 && ispunct((unsigned char)str[end_idx - 1])) {
        end_idx--;
    }

    if (end_idx < word_len) {
        return false;
    }

    size_t start_idx = end_idx - word_len;

    if (strncmp(&str[start_idx], word, word_len) != 0) {
        return false;
    }

    if (start_idx > 0 && isalnum((unsigned char)str[start_idx - 1])) {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_str1 = "Hello, world!";
    const char *test_word1 = "world";
    
    if (match_word_at_end(test_str1, test_word1)) {
        printf("Match found.\n");
    } else {
        printf("No match.\n");
    }

    return 0;
}