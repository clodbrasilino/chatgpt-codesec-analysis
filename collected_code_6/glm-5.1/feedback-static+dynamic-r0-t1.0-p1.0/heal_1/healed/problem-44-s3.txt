#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_word_at_beginning(const char *str, const char *word, size_t str_len, size_t word_len) {
    if (str == NULL || word == NULL) {
        return false;
    }

    if (word_len == 0 || word_len > str_len) {
        return false;
    }

    if (strnlen(str, str_len) < word_len) {
        return false;
    }

    if (strncmp(str, word, word_len) == 0) {
        if (word_len == str_len || str[word_len] == ' ') {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *text1 = "hello world";
    const char *text2 = "helloworld";
    const char *text3 = "hi there";
    const char *word = "hello";

    size_t text1_len = sizeof("hello world") - 1;
    size_t text2_len = sizeof("helloworld") - 1;
    size_t text3_len = sizeof("hi there") - 1;
    size_t word_len = sizeof("hello") - 1;

    bool res1 = matches_word_at_beginning(text1, word, text1_len, word_len);
    bool res2 = matches_word_at_beginning(text2, word, text2_len, word_len);
    bool res3 = matches_word_at_beginning(text3, word, text3_len, word_len);

    printf("Text1: %d\n", res1);
    printf("Text2: %d\n", res2);
    printf("Text3: %d\n", res3);

    return 0;
}