#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

bool word_exists(const char* word, const char words[][50], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

char* find_first_repeated_word(const char* str) {
    const int MAX_WORDS = 100;
    const int MAX_WORD_LENGTH = 50;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    char* mutable_str = strdup(str);
    char* token = strtok(mutable_str, " ");
    while (token && word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(token) >= MAX_WORD_LENGTH) {
            /* Possible weaknesses found:
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             */
            free(mutable_str);
            return NULL;
        }
        if (word_exists(token, words, word_count)) {
            free(mutable_str);
            return token;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

    free(mutable_str);
    return NULL;
}

int main() {
    const char* input = "This is a test string with test words";
    char* result = find_first_repeated_word(input);
    if (result != NULL) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}