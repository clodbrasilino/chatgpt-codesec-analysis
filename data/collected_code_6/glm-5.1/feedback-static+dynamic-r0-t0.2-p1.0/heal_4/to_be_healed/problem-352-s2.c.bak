#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len > 256) {
        return false;
    }

    bool *char_set = (bool *)calloc(256, sizeof(bool));
    if (char_set == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c]) {
            free(char_set);
            return false;
        }
        char_set[c] = true;
    }

    free(char_set);
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
     *  Assignment 'test3_valid=0', assigned value is 0
     */
    int test3_valid = 0;

    /* Possible weaknesses found:
     *  Condition 'test3!=NULL' is always false
     *  Condition 'test3!=NULL' is always false [knownConditionTrueFalse]
     */
    if (test3 != NULL) {
        test3_valid = 1;
    }

    if (are_characters_unique(test1)) {
        printf("%s: Unique\n", test1);
    } else {
        printf("%s: Not Unique\n", test1);
    }

    if (are_characters_unique(test2)) {
        printf("%s: Unique\n", test2);
    } else {
        printf("%s: Not Unique\n", test2);
    }

    /* Possible weaknesses found:
     *  Condition 'are_characters_unique(test3)' is always false [knownConditionTrueFalse]
     *  Condition 'are_characters_unique(test3)' is always false
     *  Calling function 'are_characters_unique' returns 0
     */
    if (are_characters_unique(test3)) {
        /* Possible weaknesses found:
         *  Condition 'test3_valid' is always false [knownConditionTrueFalse]
         *  Condition 'test3_valid' is always false
         */
        if (test3_valid) {
            printf("%s: Unique\n", test3);
        } else {
            printf("NULL: Not Unique\n");
        }
    } else {
        printf("NULL: Not Unique\n");
    }

    return 0;
}