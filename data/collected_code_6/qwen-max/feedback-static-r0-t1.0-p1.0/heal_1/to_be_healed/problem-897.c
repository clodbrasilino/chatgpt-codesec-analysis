#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isalpha'
  */

bool is_word_in_sentence(const char *sentence, const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sentence_len = strlen(sentence);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len > sentence_len) return false;

    for (size_t i = 0; i <= sentence_len - word_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'isalpha' [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'isalpha'
             *  call to undeclared library function 'isalpha' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            if (i == 0 || !isalpha(sentence[i - 1])) {
                if (i + word_len == sentence_len || !isalpha(sentence[i + word_len])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    const char *sentence = "This is a test sentence to check if the word is present";
    const char *word = "test";

    if (is_word_in_sentence(sentence, word)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}