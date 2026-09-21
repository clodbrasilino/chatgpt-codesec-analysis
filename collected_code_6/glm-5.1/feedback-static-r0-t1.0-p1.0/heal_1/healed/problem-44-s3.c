#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t max_len = 256;
    size_t word_len = strnlen(word, max_len);
    if (word_len == 0 || word_len == max_len) {
        return false;
    }

    size_t str_len = strnlen(str, max_len);
    if (str_len < word_len) {
        return false;
    }

    if (strncmp(str, word, word_len) == 0) {
        if (str[word_len] == ' ' || str[word_len] == '\0') {
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

    bool res1 = matches_word_at_beginning(text1, word);
    bool res2 = matches_word_at_beginning(text2, word);
    bool res3 = matches_word_at_beginning(text3, word);

    printf("Text1: %d\n", res1);
    printf("Text2: %d\n", res2);
    printf("Text3: %d\n", res3);

    return 0;
}