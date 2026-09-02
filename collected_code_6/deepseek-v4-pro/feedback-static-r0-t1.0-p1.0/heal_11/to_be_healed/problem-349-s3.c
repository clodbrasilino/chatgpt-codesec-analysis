#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_binary_string(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test1 = "101010";
    const char *test2 = "10201";
    const char *test3 = "";
    const char *test4 = "1";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("Test 1: %s -> %s\n", test1, 
           is_binary_string(test1) ? "binary" : "not binary");
    printf("Test 2: %s -> %s\n", test2, 
           is_binary_string(test2) ? "binary" : "not binary");
    printf("Test 3: %s -> %s\n", test3, 
           is_binary_string(test3) ? "binary" : "not binary");
    printf("Test 4: %s -> %s\n", test4, 
           is_binary_string(test4) ? "binary" : "not binary");
    /* Possible weaknesses found:
     *  Condition 'test5' is always false [knownConditionTrueFalse]
     *  Condition 'test5' is always false
     */
    printf("Test 5: %s -> %s\n", test5 ? test5 : "(null)", 
           /* Possible weaknesses found:
            *  Condition 'is_binary_string(test5)' is always false [knownConditionTrueFalse]
            *  Condition 'is_binary_string(test5)' is always false
            *  Calling function 'is_binary_string' returns 0
            */
           is_binary_string(test5) ? "binary" : "not binary");
    
    return 0;
}