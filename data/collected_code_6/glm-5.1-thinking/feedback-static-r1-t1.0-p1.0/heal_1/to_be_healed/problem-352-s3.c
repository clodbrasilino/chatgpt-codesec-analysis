#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool char_set[UCHAR_MAX + 1] = {false};

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
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
    /* Possible weaknesses found:
     *  Assignment 'test3=NULL', assigned value is 0
     */
    const char *test3 = NULL;
    const char *test4 = "";

    printf("%s: %s\n", test1 ? test1 : "NULL", are_characters_unique(test1) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2 ? test2 : "NULL", are_characters_unique(test2) ? "Unique" : "Not Unique");
    /* Possible weaknesses found:
     *  Condition 'are_characters_unique(test3)' is always false
     *  Condition 'test3' is always false
     *  Condition 'test3' is always false [knownConditionTrueFalse]
     *  Condition 'are_characters_unique(test3)' is always false [knownConditionTrueFalse]
     *  Calling function 'are_characters_unique' returns 0
     */
    printf("%s: %s\n", test3 ? test3 : "NULL", are_characters_unique(test3) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test4 ? test4 : "NULL", are_characters_unique(test4) ? "Unique" : "Not Unique");

    return 0;
}