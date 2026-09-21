#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool match_word_at_start(const char *str, const char *word)
{
    size_t word_len;

    if (str == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }

    if (strncmp(str, word, word_len) != 0) {
        return false;
    }

    if (str[word_len] != '\0' && isalnum((unsigned char)str[word_len])) {
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
            return EXIT_FAILURE;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word1, text) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (match_word_at_start(text, word2)) {
        if (printf("'%s' matches at the start of '%s'\n", word2, text) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word2, text) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (match_word_at_start(text, word3)) {
        if (printf("'%s' matches at the start of '%s'\n", word3, text) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("'%s' does not match at the start of '%s'\n", word3, text) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}