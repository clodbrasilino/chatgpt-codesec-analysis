#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return true;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return (strlen(word) % 2) == 0;
}

int main(void) {
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";

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
     *  Calling function 'is_length_even' returns 1
     *  Condition 'is_length_even(NULL)' is always true
     *  Condition 'is_length_even(NULL)' is always true [knownConditionTrueFalse]
     */
    if (is_length_even(NULL)) {
        printf("NULL has even length\n");
    } else {
        printf("NULL has odd length\n");
    }

    return 0;
}