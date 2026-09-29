#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len == 0 || word_len > str_len) {
        return 0;
    }

    size_t pos = str_len - word_len;

    if (strncmp(str + pos, word, word_len) != 0) {
        return 0;
    }

    if (pos > 0) {
        char prev = str[pos - 1];
        if (isalnum((unsigned char)prev) || prev == '_') {
            return 0;
        }
    }

    size_t end = str_len;
    while (end > pos + word_len) {
        char c = str[end - 1];
        if (!ispunct((unsigned char)c)) {
            break;
        }
        end--;
    }

    if (end == pos + word_len) {
        return 1;
    }

    if (end == str_len - 1) {
        char c = str[end];
        if (ispunct((unsigned char)c)) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    printf("%d\n", match_word_at_end("Hello, world", "world"));
    printf("%d\n", match_word_at_end("Hello, world!", "world"));
    printf("%d\n", match_word_at_end("Hello, world!!!", "world"));
    printf("%d\n", match_word_at_end("Hello, worldly", "world"));
    printf("%d\n", match_word_at_end("Hello, underworld", "world"));
    printf("%d\n", match_word_at_end("Hello, World", "world"));
    printf("%d\n", match_word_at_end("world", "world"));
    printf("%d\n", match_word_at_end("world!", "world"));
    printf("%d\n", match_word_at_end("", "world"));
    printf("%d\n", match_word_at_end("Hello", ""));

    return 0;
}