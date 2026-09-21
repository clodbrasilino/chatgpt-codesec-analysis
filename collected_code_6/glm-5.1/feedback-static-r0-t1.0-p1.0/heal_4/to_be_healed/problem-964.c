#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return (len % 2) == 0;
}

int main(void) {
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";
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
        printf("Empty string has odd length\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'is_length_even' returns 0
     *  Condition 'is_length_even(word4,0)' is always false [knownConditionTrueFalse]
     *  Condition 'is_length_even(word4,0)' is always false
     */
    if (is_length_even(word4, 0)) {
        printf("NULL has even length\n");
    } else {
        printf("NULL has odd length\n");
    }

    return 0;
}