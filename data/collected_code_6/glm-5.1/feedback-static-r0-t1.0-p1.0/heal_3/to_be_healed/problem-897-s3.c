#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }

    const char *s_ptr = sentence;
    const char *w_ptr = word;

    while (*s_ptr != '\0') {
        if (*w_ptr == '\0') {
            if (isspace((unsigned char)*s_ptr)) {
                const char *before = s_ptr - word_len;
                if (before == sentence || isspace((unsigned char)*(before - 1))) {
                    return true;
                }
            }
            w_ptr = word;
        }

        if (*s_ptr == *w_ptr) {
            w_ptr++;
        } else {
            w_ptr = word;
            if (*s_ptr == *w_ptr) {
                w_ptr++;
            }
        }
        s_ptr++;
    }

    if (*w_ptr == '\0') {
        const char *before = s_ptr - word_len;
        bool match_before = (before == sentence) || (before > sentence && isspace((unsigned char)*(before - 1)));
        if (match_before) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps over the lazy dog";
    const char *word1 = "fox";
    const char *word2 = "cat";
    const char *word3 = "jump";

    if (is_word_present(sentence, word1)) {
        printf("'%s' is present in the sentence.\n", word1);
    } else {
        printf("'%s' is not present in the sentence.\n", word1);
    }

    if (is_word_present(sentence, word2)) {
        printf("'%s' is present in the sentence.\n", word2);
    } else {
        printf("'%s' is not present in the sentence.\n", word2);
    }

    if (is_word_present(sentence, word3)) {
        printf("'%s' is present in the sentence.\n", word3);
    } else {
        printf("'%s' is not present in the sentence.\n", word3);
    }

    return 0;
}