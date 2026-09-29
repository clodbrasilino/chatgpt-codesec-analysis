#include <stdio.h>
#include <string.h>
#include <ctype.h>

static size_t safe_strlen(const char *str, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

int word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    size_t str_len = safe_strlen(str, 4096);
    size_t word_len = safe_strlen(word, 4096);

    if (word_len == 0 || str_len == 0) {
        return 0;
    }

    if (word_len > str_len) {
        return 0;
    }

    size_t pos = str_len;

    while (pos > 0 && (ispunct((unsigned char)str[pos - 1]) || isspace((unsigned char)str[pos - 1]))) {
        pos--;
    }

    if (pos < word_len) {
        return 0;
    }

    size_t word_start = pos - word_len;

    if (word_start > 0 && (isalnum((unsigned char)str[word_start - 1]) || str[word_start - 1] == '_')) {
        return 0;
    }

    return strncmp(str + word_start, word, word_len) == 0;
}

int main(void) {
    printf("%d\n", word_at_end("hello world", "world"));
    printf("%d\n", word_at_end("hello world!", "world"));
    printf("%d\n", word_at_end("hello world,", "world"));
    printf("%d\n", word_at_end("hello world?", "world"));
    printf("%d\n", word_at_end("hello worlds", "world"));
    printf("%d\n", word_at_end("hello world", "worl"));
    printf("%d\n", word_at_end("hello", "hello"));
    printf("%d\n", word_at_end("", "world"));
    printf("%d\n", word_at_end(NULL, "world"));
    printf("%d\n", word_at_end("hello world!", ""));
    return 0;
}