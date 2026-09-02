#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isalpha'
  */

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }
    
    int sentence_len = strlen(sentence);
    int word_len = strlen(word);
    
    for (int i = 0; i <= sentence_len - word_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            /* Possible weaknesses found:
             *  include the header <ctype.h> or explicitly provide a declaration for 'isalpha'
             *  call to undeclared library function 'isalpha' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'isalpha' [-Wimplicit-function-declaration]
             */
            if (i == 0 && !isalpha(sentence[word_len])) {
                return 1;
            } else if (i > 0 && !isalpha(sentence[i - 1]) && !isalpha(sentence[i + word_len])) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'sentence' can be declared as const array [constVariable]
     */
    char sentence[] = "This is a sample sentence with several words";
    char word[] = "sample";

    if (is_word_present(sentence, word)) {
        printf("Word '%s' is present in the sentence.\n", word);
    } else {
        printf("Word '%s' is not present in the sentence.\n", word);
    }

    return 0;
}