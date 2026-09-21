#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool match_word_at_end(const char *str, size_t str_max_len, const char *word, size_t word_max_len) {
    if (!str || !word) {
        return false;
    }

    size_t str_len = strnlen(str, str_max_len);
    size_t word_len = strnlen(word, word_max_len);

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

    if (match_word_at_end(test_str, 1024, word_to_match, 256)) {
        printf("Match found!\n");
    } else {
        printf("Match not found.\n");
    }

    return 0;
}