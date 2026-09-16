#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int match_word_at_start(const char *str, const char *word)
{
    size_t word_len;
    size_t i;

    if (str == NULL || word == NULL) {
        return 0;
    }

    word_len = strlen(word);
    if (word_len == 0) {
        return 0;
    }

    for (i = 0; i < word_len; i++) {
        if (str[i] == '\0' || str[i] != word[i]) {
            return 0;
        }
    }

    if (str[word_len] == '\0' || isspace((unsigned char)str[word_len]) ||
        ispunct((unsigned char)str[word_len])) {
        return 1;
    }

    return 0;
}

int main(void)
{
    const char *text1 = "hello world";
    const char *text2 = "helloworld";
    const char *text3 = "hello, everyone";
    const char *word = "hello";
    int result;

    result = match_word_at_start(text1, word);
    if (printf("Match in \"%s\": %d\n", text1, result) < 0) {
        return EXIT_FAILURE;
    }

    result = match_word_at_start(text2, word);
    if (printf("Match in \"%s\": %d\n", text2, result) < 0) {
        return EXIT_FAILURE;
    }

    result = match_word_at_start(text3, word);
    if (printf("Match in \"%s\": %d\n", text3, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}