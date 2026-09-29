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
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    /* Possible weaknesses found:
     *  Assignment 'test3=NULL', assigned value is 0
     */
    const char *test3 = NULL;
    const char *test4 = "";

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

    /* Possible weaknesses found:
     *  Condition 'test3==NULL' is always true
     *  Condition 'test3==NULL' is always true [knownConditionTrueFalse]
     */
    if (test3 == NULL) {
        printf("NULL string does not have all unique characters\n");
    } else if (are_characters_unique(test3, 256)) {
        printf("\"%s\" has all unique characters\n", test3);
    } else {
        printf("\"%s\" does not have all unique characters\n", test3);
    }

    if (are_characters_unique(test4, 256)) {
        printf("\"%s\" has all unique characters\n", test4);
    } else {
        printf("\"%s\" does not have all unique characters\n", test4);
    }

    return 0;
}