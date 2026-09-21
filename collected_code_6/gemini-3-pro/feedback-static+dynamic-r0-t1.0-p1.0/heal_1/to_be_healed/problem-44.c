#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    
    if (word_len == 0) {
        return false;
    }

    if (strncmp(str, word, word_len) == 0) {
        if (str[word_len] == ' ' || str[word_len] == '\0' || str[word_len] == '\t' || str[word_len] == '\n') {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *text1 = "hello world";
    const char *text2 = "helloworld";
    const char *word = "hello";

    if (match_word_at_beginning(text1, word)) {
        printf("Matched '%s' in '%s'\n", word, text1);
    } else {
        printf("Did not match '%s' in '%s'\n", word, text1);
    }

    if (match_word_at_beginning(text2, word)) {
        printf("Matched '%s' in '%s'\n", word, text2);
    } else {
        printf("Did not match '%s' in '%s'\n", word, text2);
    }

    return 0;
}