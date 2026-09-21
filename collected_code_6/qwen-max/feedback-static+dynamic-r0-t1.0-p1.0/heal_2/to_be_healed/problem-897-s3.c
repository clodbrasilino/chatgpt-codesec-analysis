#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

bool is_word_in_sentence(const char *sentence, const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    size_t sentence_len = strnlen(sentence, 1024);

    if (word_len > sentence_len) {
        return false;
    }

    for (size_t i = 0; i <= sentence_len - word_len; ++i) {
        if (strncmp(&sentence[i], word, word_len) == 0) {
            /* Possible weaknesses found:
             *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
             *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
             */
            if (i + word_len < sentence_len && !isspace((unsigned char)sentence[i + word_len])) {
                continue;
            }
            if (i > 0 && !isspace((unsigned char)sentence[i - 1])) {
                continue;
            }
            return true;
        }
    }
    return false;
}

int main() {
    const char *sentence = "This is a sample sentence with several words.";
    const char *word = "sample";
    bool found = is_word_in_sentence(sentence, word);
    if (found) {
        printf("The word '%s' is present in the sentence.\n", word);
    } else {
        printf("The word '%s' is not present in the sentence.\n", word);
    }
    return 0;
}