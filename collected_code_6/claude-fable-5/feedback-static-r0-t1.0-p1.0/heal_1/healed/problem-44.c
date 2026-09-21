#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

bool match_word_at_start(const char *str, const char *word)
{
    size_t word_len;

    if (str == NULL || word == NULL) {
        return false;
    }

    word_len = strnlen(word, MAX_WORD_LEN);
    if (word_len == 0 || word_len >= MAX_WORD_LEN) {
        return false;
    }

    if (strncmp(str, word, word_len) != 0) {
        return false;
    }

    if (str[word_len] == '\0') {
        return true;
    }

    if (isalnum((unsigned char)str[word_len]) || str[word_len] == '_') {
        return false;
    }

    return true;
}

int main(void)
{
    const char *text = "hello world";
    const char *word1 = "hello";
    const char *word2 = "hell";
    const char *word3 = "world";

    if (match_word_at_start(text, word1)) {
        if (printf("'%s' matches at the start of '%s'\n", word1, text) < 0) {
            return 1;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word1, text) < 0) {
            return 1;
        }
    }

    if (match_word_at_start(text, word2)) {
        if (printf("'%s' matches at the start of '%s'\n", word2, text) < 0) {
            return 1;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word2, text) < 0) {
            return 1;
        }
    }

    if (match_word_at_start(text, word3)) {
        if (printf("'%s' matches at the start of '%s'\n", word3, text) < 0) {
            return 1;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word3, text) < 0) {
            return 1;
        }
    }

    return 0;
}