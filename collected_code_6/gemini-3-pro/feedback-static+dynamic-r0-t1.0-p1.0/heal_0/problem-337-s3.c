#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0) {
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

    if (strncmp(&str[start_idx], word, word_len) == 0) {
        if (start_idx == 0 || isspace((unsigned char)str[start_idx - 1]) || ispunct((unsigned char)str[start_idx - 1])) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test_str1 = "Hello, this is a test.";
    const char *test_word1 = "test";
    
    const char *test_str2 = "Another example string!";
    const char *test_word2 = "string";

    const char *test_str3 = "Not matching fail";
    const char *test_word3 = "match";

    printf("%d\n", match_word_at_end(test_str1, test_word1));
    printf("%d\n", match_word_at_end(test_str2, test_word2));
    printf("%d\n", match_word_at_end(test_str3, test_word3));

    return 0;
}