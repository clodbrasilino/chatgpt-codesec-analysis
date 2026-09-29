#include <stdio.h>
#include <stdbool.h>

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first = str[0];
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assignment 'i=1', assigned value is 1
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     */
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abca";
    const char *test3 = "";
    const char *test4 = "b";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("Test 1 (\"%s\"): %s\n", test1, all_characters_same(test1) ? "true" : "false");
    printf("Test 2 (\"%s\"): %s\n", test2, all_characters_same(test2) ? "true" : "false");
    printf("Test 3 (\"%s\"): %s\n", test3, all_characters_same(test3) ? "true" : "false");
    printf("Test 4 (\"%s\"): %s\n", test4, all_characters_same(test4) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always false
     *  Condition 'test5!=NULL' is always false [knownConditionTrueFalse]
     */
    if (test5 != NULL) {
        printf("Test 5 (\"%s\"): %s\n", test5, all_characters_same(test5) ? "true" : "false");
    } else {
        printf("Test 5 (NULL): false\n");
    }
    
    return 0;
}