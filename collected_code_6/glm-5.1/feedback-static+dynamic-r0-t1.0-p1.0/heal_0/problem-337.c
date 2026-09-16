#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, const char *word) {
    size_t str_len;
    size_t word_len;

    if (str == NULL || word == NULL) {
        return 0;
    }

    str_len = strlen(str);
    word_len = strlen(word);

    if (word_len == 0) {
        return 0;
    }

    if (str_len < word_len) {
        return 0;
    }

    const char *str_end = str + str_len - word_len;
    if (strcmp(str_end, word) != 0) {
        return 0;
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