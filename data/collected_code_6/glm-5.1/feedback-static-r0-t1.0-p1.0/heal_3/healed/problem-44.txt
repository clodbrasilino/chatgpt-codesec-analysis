#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_word_at_start(const char *str, const char *word, size_t str_len, size_t word_len) {
    if (str == NULL || word == NULL) {
        return 0;
    }

    if (word_len == 0 || str_len < word_len) {
        return 0;
    }

    if (strncmp(str, word, word_len) != 0) {
        return 0;
    }

    if (str_len == word_len) {
        return 1;
    }

    char next_char = str[word_len];
    if (next_char == ' ' || next_char == '\t' || next_char == '\n' || next_char == '\r' || next_char == '\0') {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *text1 = "hello world";
    const char *text2 = "helloworld";
    const char *text3 = "hi there";
    const char *text4 = "test";
    const char *text5 = NULL;

    if (match_word_at_start(text1, "hello", 11, 5)) {
        printf("Match 1\n");
    }

    if (!match_word_at_start(text2, "hello", 10, 5)) {
        printf("No Match 2\n");
    }

    if (match_word_at_start(text3, "hi", 8, 2)) {
        printf("Match 3\n");
    }

    if (match_word_at_start(text4, "test", 4, 4)) {
        printf("Match 4\n");
    }

    if (!match_word_at_start(text5, "any", 0, 3)) {
        printf("No Match 5\n");
    }

    return 0;
}