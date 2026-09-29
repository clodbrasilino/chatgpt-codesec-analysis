#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len > 256) {
        return false;
    }

    bool char_set[256] = {false};

    for (size_t i = 0; i < len; i++) {
        uint8_t c = (uint8_t)str[i];
        if (char_set[c]) {
            return false;
        }
        char_set[c] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    /* Possible weaknesses found:
     *  Assignment 'test4=NULL', assigned value is 0
     */
    const char *test4 = NULL;
    const char *test5 = "aabbcc";

    printf("\"%s\" %s all unique characters\n", test1, are_characters_unique(test1) ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test2, are_characters_unique(test2) ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test3, are_characters_unique(test3) ? "has" : "does not have");
    /* Possible weaknesses found:
     *  Condition 'are_characters_unique(test4)' is always false [knownConditionTrueFalse]
     *  Condition 'test4' is always false
     *  Calling function 'are_characters_unique' returns 0
     *  Condition 'test4' is always false [knownConditionTrueFalse]
     *  Condition 'are_characters_unique(test4)' is always false
     */
    printf("\"%s\" %s all unique characters\n", test4 ? test4 : "NULL", are_characters_unique(test4) ? "has" : "does not have");
    printf("\"%s\" %s all unique characters\n", test5, are_characters_unique(test5) ? "has" : "does not have");

    return 0;
}