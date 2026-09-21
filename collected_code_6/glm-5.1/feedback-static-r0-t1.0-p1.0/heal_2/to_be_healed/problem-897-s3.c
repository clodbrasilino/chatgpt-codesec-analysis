#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    const char *s_ptr = sentence;
    const char *w_ptr = word;

    while (*s_ptr != '\0') {
        if (*w_ptr == '\0') {
            /* Possible weaknesses found:
             *  Condition '*s_ptr=='\0'' is always false [knownConditionTrueFalse]
             */
            if (*s_ptr == '\0' || isspace((unsigned char)*s_ptr)) {
                return true;
            }
            w_ptr = word;
        } else if (*s_ptr == *w_ptr) {
            w_ptr++;
        } else {
            w_ptr = word;
        }
        s_ptr++;
    }

    if (*w_ptr == '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        bool match_before = (sentence == s_ptr - strlen(word)) || isspace((unsigned char)*(s_ptr - strlen(word) - 1));
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