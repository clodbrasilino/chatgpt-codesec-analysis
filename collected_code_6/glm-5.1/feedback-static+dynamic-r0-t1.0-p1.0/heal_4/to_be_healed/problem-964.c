#include <stdio.h>
#include <stdbool.h>

bool is_length_even(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return (len % 2) == 0;
}

int main(void) {
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";

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

    const char *null_str = NULL;
    /* Possible weaknesses found:
     *  Condition 'is_length_even(null_str,0)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_length_even' returns 0
     *  Condition 'is_length_even(null_str,0)' is always false
     */
    if (is_length_even(null_str, 0)) {
        printf("NULL has even length\n");
    } else {
        printf("NULL has odd length\n");
    }

    return 0;
}