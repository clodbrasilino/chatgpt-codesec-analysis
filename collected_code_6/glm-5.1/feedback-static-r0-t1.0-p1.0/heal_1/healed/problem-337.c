#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, const char *word) {
    size_t str_len;
    size_t word_len;

    if (str == NULL || word == NULL) {
        return 0;
    }

    if (str[0] == '\0' || word[0] == '\0') {
        return 0;
    }

    str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
    }

    word_len = 0;
    while (word[word_len] != '\0') {
        word_len++;
    }

    if (str_len < word_len) {
        return 0;
    }

    const char *str_end = str + str_len - word_len;
    size_t i;
    for (i = 0; i < word_len; i++) {
        if (str_end[i] != word[i]) {
            return 0;
        }
    }

    if (str_len == word_len) {
        return 1;
    }

    char preceding = *(str_end - 1);
    if (isspace((unsigned char)preceding) || ispunct((unsigned char)preceding)) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test1 = "Hello world";
    const char *test2 = "Hello world.";
    const char *test3 = "Hello world!";
    const char *test4 = "Hello under world";
    const char *test5 = "world";

    printf("%d\n", match_word_at_end(test1, "world"));
    printf("%d\n", match_word_at_end(test2, "world"));
    printf("%d\n", match_word_at_end(test3, "world"));
    printf("%d\n", match_word_at_end(test4, "world"));
    printf("%d\n", match_word_at_end(test5, "world"));
    printf("%d\n", match_word_at_end(NULL, "world"));
    printf("%d\n", match_word_at_end(test1, NULL));

    return 0;
}