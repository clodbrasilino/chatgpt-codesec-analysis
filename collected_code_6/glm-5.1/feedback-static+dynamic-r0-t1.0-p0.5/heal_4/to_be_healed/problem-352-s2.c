#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_chars_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool seen[256] = {false};

    for (size_t i = 0; str[i] != '\0'; i++) {
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

    if (are_chars_unique(test1)) {
        printf("%s: Unique\n", test1);
    } else {
        printf("%s: Not Unique\n", test1);
    }

    if (are_chars_unique(test2)) {
        printf("%s: Unique\n", test2);
    } else {
        printf("%s: Not Unique\n", test2);
    }

    /* Possible weaknesses found:
     *  Condition 'test3!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'test3!=NULL' is always false
     */
    if (test3 != NULL && are_chars_unique(test3)) {
        printf("%s: Unique\n", test3);
    } else {
        printf("NULL: Not Unique\n");
    }

    return 0;
}