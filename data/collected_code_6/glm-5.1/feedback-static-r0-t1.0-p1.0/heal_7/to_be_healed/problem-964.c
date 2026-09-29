#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL || max_len == 0) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return (len % 2) == 0;
}

int main(void) {
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";
    /* Possible weaknesses found:
     *  Assignment 'word4=NULL', assigned value is 0
     */
    const char *word4 = NULL;

    if (is_length_even(word1, sizeof(word1))) {
        printf("%s has even length\n", word1);
    } else {
        printf("%s has odd length\n", word1);
    }

    if (is_length_even(word2, sizeof(word2))) {
        printf("%s has even length\n", word2);
    } else {
        printf("%s has odd length\n", word2);
    }

    if (is_length_even(word3, sizeof(word3))) {
        printf("Empty string has even length\n");
    } else {
        /* Possible weaknesses found:
         *  printf format string requires 0 parameters but 1 is given. [wrongPrintfScanfArgNum]
         */
        printf("Empty string has odd length\n", word3);
    }

    /* Possible weaknesses found:
     *  Condition 'word4!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'word4!=NULL' is always false
     */
    if (word4 != NULL) {
        if (is_length_even(word4, 8)) {
            printf("%s has even length\n", word4);
        } else {
            printf("%s has odd length\n", word4);
        }
    } else {
        printf("Null string provided\n");
    }

    return 0;
}