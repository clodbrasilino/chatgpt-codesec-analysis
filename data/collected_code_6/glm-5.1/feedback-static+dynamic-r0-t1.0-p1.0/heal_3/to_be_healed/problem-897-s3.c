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
    size_t sentence_len = strlen(sentence);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);

    if (word_len == 0 || sentence_len < word_len) {
        return false;
    }

    for (size_t i = 0; i <= sentence_len - word_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            bool match_before = (i == 0) || isspace((unsigned char)sentence[i - 1]);
            bool match_after = (i + word_len == sentence_len) || isspace((unsigned char)sentence[i + word_len]);

            if (match_before && match_after) {
                return true;
            }
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
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (is_word_present(sentence, word2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (is_word_present(sentence, word3)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}