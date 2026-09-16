#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool match_word_at_end(const char *str, const char *word) {
    if (!str || !word) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len < word_len) {
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

    if (start_idx > 0 && !isspace((unsigned char)str[start_idx - 1])) {
        return false;
    }

    if (strncmp(str + start_idx, word, word_len) != 0) {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_str = "This is a simple test!!!";
    const char *word_to_match = "test";

    if (match_word_at_end(test_str, word_to_match)) {
        printf("Match found!\n");
    } else {
        printf("Match not found.\n");
    }

    return 0;
}