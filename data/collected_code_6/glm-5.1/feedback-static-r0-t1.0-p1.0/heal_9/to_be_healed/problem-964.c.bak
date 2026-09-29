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
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";
    /* Possible weaknesses found:
     *  Assignment 'word4=NULL', assigned value is 0
     */
    const char *word4 = NULL;
    const char *word5 = "test";

    /* Possible weaknesses found:
     *  Condition 'is_length_even(word4)' is always false
     *  Calling function 'is_length_even' returns 0
     *  Condition 'is_length_even(word4)' is always false [knownConditionTrueFalse]
     */
    if (is_length_even(word4)) {
        printf("%s has even length\n", word4);
    /* Possible weaknesses found:
     *  Condition 'word4!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'word4!=NULL' is always false
     */
    } else if (word4 != NULL && !is_length_even(word4)) {
        printf("%s has odd length\n", word4);
    } else {
        printf("Pointer is NULL\n");
    }

    if (is_length_even(word5)) {
        printf("%s has even length\n", word5);
    } else {
        printf("%s has odd length\n", word5);
    }

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
     *  Condition 'word4==NULL' is always true
     *  Condition 'word4==NULL' is always true [knownConditionTrueFalse]
     */
    if (word4 == NULL) {
        printf("NULL does not have a valid length\n");
    } else if (is_length_even(word4)) {
        printf("NULL has even length\n");
    } else {
        printf("NULL has odd length\n");
    }

    return 0;
}