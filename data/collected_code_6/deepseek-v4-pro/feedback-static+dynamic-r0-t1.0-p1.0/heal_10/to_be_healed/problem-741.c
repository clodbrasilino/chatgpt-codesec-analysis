#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first = str[0];
    /* Possible weaknesses found:
     *  Assignment 'i=1', assigned value is 1
     */
    size_t i = 1;
    
    /* Possible weaknesses found:
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     *  Array index out of bounds
     */
    while (str[i] != '\0') {
        if (str[i] != first) {
            return false;
        }
        i++;
    }
    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abca";
    const char *test3 = "";
    const char *test4 = "b";
    const char *test5 = NULL;
    
    printf("Test 1 (\"%s\"): %s\n", test1, all_characters_same(test1) ? "True" : "False");
    printf("Test 2 (\"%s\"): %s\n", test2, all_characters_same(test2) ? "True" : "False");
    printf("Test 3 (\"%s\"): %s\n", test3, all_characters_same(test3) ? "True" : "False");
    printf("Test 4 (\"%s\"): %s\n", test4, all_characters_same(test4) ? "True" : "False");
    /* Possible weaknesses found:
     *  Calling function 'all_characters_same' returns 0
     *  Condition 'all_characters_same(test5)' is always false
     *  Condition 'all_characters_same(test5)' is always false [knownConditionTrueFalse]
     */
    printf("Test 5 (NULL): %s\n", all_characters_same(test5) ? "True" : "False");
    
    return 0;
}