#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    return (len % 2) == 0;
}

int main(void) {
    char word1[] = "hello";
    char word2[] = "world!";
    /* Possible weaknesses found:
     *  Variable 'word3' can be declared as const array [constVariable]
     */
    char word3[] = "";

    if (is_length_even(word1)) {
        printf("%s has even length\n", word1);
    } else {
        printf("%s has odd length\n", word1);
    }

    if (is_length_even(word2)) {
        printf("%s has even length\n", word2);
    } else {
        printf("%s has odd length\n", word2);
    }

    if (is_length_even(word3)) {
        printf("Empty string has even length\n");
    } else {
        printf("Empty string has odd length\n");
    }

    /* Possible weaknesses found:
     *  Condition 'is_length_even(NULL)' is always false
     *  Calling function 'is_length_even' returns 0
     *  Condition 'is_length_even(NULL)' is always false [knownConditionTrueFalse]
     */
    if (is_length_even(NULL)) {
        printf("NULL has even length\n");
    } else {
        printf("NULL has odd length\n");
    }

    return 0;
}