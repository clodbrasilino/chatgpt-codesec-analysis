#include <stdio.h>
#include <stdbool.h>

bool are_characters_unique(const char *str) {
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

    printf("%s: %s\n", test1 ? test1 : "(null)", are_characters_unique(test1) ? "true" : "false");
    printf("%s: %s\n", test2 ? test2 : "(null)", are_characters_unique(test2) ? "true" : "false");
    /* Possible weaknesses found:
     *  Calling function 'are_characters_unique' returns 0
     *  Condition 'test3' is always false
     *  Condition 'test3' is always false [knownConditionTrueFalse]
     *  Condition 'are_characters_unique(test3)' is always false
     *  Condition 'are_characters_unique(test3)' is always false [knownConditionTrueFalse]
     */
    printf("%s: %s\n", test3 ? test3 : "(null)", are_characters_unique(test3) ? "true" : "false");

    return 0;
}