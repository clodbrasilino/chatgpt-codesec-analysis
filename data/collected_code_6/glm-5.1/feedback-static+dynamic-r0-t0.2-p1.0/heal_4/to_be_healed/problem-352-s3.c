#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_characters_unique(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    bool char_set[256] = {false};

    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
        unsigned char c = (unsigned char)str[i];
        if (char_set[c]) {
            return false;
        }
        char_set[c] = true;
    }

    return true;
}

int main(void) {
    const char * const test1 = "abcdef";
    const char * const test2 = "hello";
    const char * const test3 = "";
    const char *test4 = NULL;

    if (are_characters_unique(test1, 256)) {
        printf("\"%s\" has all unique characters\n", test1);
    } else {
        printf("\"%s\" does not have all unique characters\n", test1);
    }

    if (are_characters_unique(test2, 256)) {
        printf("\"%s\" has all unique characters\n", test2);
    } else {
        printf("\"%s\" does not have all unique characters\n", test2);
    }

    if (are_characters_unique(test3, 256)) {
        printf("\"%s\" has all unique characters\n", test3);
    } else {
        printf("\"%s\" does not have all unique characters\n", test3);
    }

    /* Possible weaknesses found:
     *  Condition 'are_characters_unique(test4,256)' is always false
     *  Condition 'are_characters_unique(test4,256)' is always false [knownConditionTrueFalse]
     *  Calling function 'are_characters_unique' returns 0
     */
    if (are_characters_unique(test4, 256)) {
        printf("\"(null)\" has all unique characters\n");
    } else {
        printf("\"(null)\" does not have all unique characters\n");
    }

    return 0;
}