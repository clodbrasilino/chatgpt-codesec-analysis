#include <stdio.h>
#include <string.h>
#include <ctype.h>

int word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len == 0) {
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