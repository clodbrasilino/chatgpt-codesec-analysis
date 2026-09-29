#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, size_t str_len, const char *word, size_t word_len) {
    size_t effective_str_len;
    const char *p;

    if (str == NULL || word == NULL || str_len == 0 || word_len == 0) {
        return 0;
    }

    p = str + str_len - 1;

    while (p >= str && ispunct((unsigned char)*p)) {
        p--;
    }

    if (p < str) {
        return 0;
    }

    effective_str_len = (size_t)(p - str + 1);

    if (effective_str_len < word_len) {
        return 0;
    }

    if (effective_str_len > word_len) {
        if (!isspace((unsigned char)str[effective_str_len - word_len - 1])) {
            return 0;
        }
    }

    for (size_t i = 0; i < word_len; i++) {
        if (str[effective_str_len - word_len + i] != word[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    const char *test_str1 = "Hello world!";
    const char *test_str2 = "Hello world";
    const char *test_str3 = "world";
    const char *test_str4 = "Helloworld";
    const char *test_str5 = "Hello world...";
    const char *test_str6 = "Hello world, how are you?";
    const char *test_word = "world";
    size_t len1 = strnlen(test_str1, 256);
    size_t len2 = strnlen(test_str2, 256);
    size_t len3 = strnlen(test_str3, 256);
    size_t len4 = strnlen(test_str4, 256);
    size_t len5 = strnlen(test_str5, 256);
    size_t len6 = strnlen(test_str6, 256);
    size_t word_len = strnlen(test_word, 256);

    printf("%d\n", match_word_at_end(test_str1, len1, test_word, word_len));
    printf("%d\n", match_word_at_end(test_str2, len2, test_word, word_len));
    printf("%d\n", match_word_at_end(test_str3, len3, test_word, word_len));
    printf("%d\n", match_word_at_end(test_str4, len4, test_word, word_len));
    printf("%d\n", match_word_at_end(test_str5, len5, test_word, word_len));
    printf("%d\n", match_word_at_end(test_str6, len6, test_word, word_len));

    return 0;
}