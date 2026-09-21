#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_chars_unique(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }

    if (len > 256) {
        return false;
    }

    bool seen[256] = { false };

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    /* Possible weaknesses found:
     *  Assignment 'test3=NULL', assigned value is 0
     */
    const char *test3 = NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (are_chars_unique(test1, test1 ? strlen(test1) : 0)) {
        printf("\"%s\" has all unique characters.\n", test1);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test1);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (are_chars_unique(test2, test2 ? strlen(test2) : 0)) {
        printf("\"%s\" has all unique characters.\n", test2);
    } else {
        printf("\"%s\" does not have all unique characters.\n", test2);
    }

    /* Possible weaknesses found:
     *  Condition 'are_chars_unique(test3,test3?strlen(test3):0)' is always false
     *  Condition 'test3' is always false [knownConditionTrueFalse]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'are_chars_unique(test3,test3?strlen(test3):0)' is always false [knownConditionTrueFalse]
     *  Condition 'test3' is always false
     *  Calling function 'are_chars_unique' returns 0
     */
    if (are_chars_unique(test3, test3 ? strlen(test3) : 0)) {
        printf("NULL string has all unique characters.\n");
    } else {
        printf("NULL string does not have all unique characters.\n");
    }

    return 0;
}