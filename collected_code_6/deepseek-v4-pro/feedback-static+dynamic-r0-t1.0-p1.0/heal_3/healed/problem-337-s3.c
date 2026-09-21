#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    const char *s = str;
    const char *w = word;

    while (*w != '\0' && *s != '\0') {
        w++;
        s++;
    }

    if (*w != '\0') {
        return 0;
    }

    s = str;
    while (*s != '\0') {
        s++;
    }

    size_t word_len = (size_t)(w - word);

    if (word_len == 0) {
        return 0;
    }

    size_t str_len = (size_t)(s - str);

    if (word_len > str_len) {
        return 0;
    }

    size_t pos = str_len - word_len;

    for (size_t i = 0; i < word_len; i++) {
        if (str[pos + i] != word[i]) {
            return 0;
        }
    }

    if (pos > 0) {
        unsigned char prev = (unsigned char)str[pos - 1];
        if (isalnum(prev) || prev == '_') {
            return 0;
        }
    }

    size_t end = str_len;
    while (end > pos + word_len) {
        unsigned char c = (unsigned char)str[end - 1];
        if (!ispunct(c)) {
            break;
        }
        end--;
    }

    if (end == pos + word_len) {
        return 1;
    }

    if (end == str_len) {
        return 1;
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