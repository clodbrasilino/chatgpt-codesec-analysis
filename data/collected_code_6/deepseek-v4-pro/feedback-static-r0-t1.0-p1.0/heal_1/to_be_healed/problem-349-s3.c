#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    /* Possible weaknesses found:
     *  Assignment 'test1="101010"', assigned value is "101010"
     */
    const char *test1 = "101010";
    /* Possible weaknesses found:
     *  Assignment 'test2="10201"', assigned value is "10201"
     */
    const char *test2 = "10201";
    /* Possible weaknesses found:
     *  Assignment 'test3=""', assigned value is ""
     */
    const char *test3 = "";
    /* Possible weaknesses found:
     *  Assignment 'test4="1"', assigned value is "1"
     */
    const char *test4 = "1";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    /* Possible weaknesses found:
     *  Condition 'test1!=NULL' is always true
     *  Condition 'test1!=NULL' is always true [knownConditionTrueFalse]
     */
    printf("Test 1: %s -> %s\n", test1 != NULL ? test1 : "(null)", 
           is_binary_string(test1) ? "binary" : "not binary");
    /* Possible weaknesses found:
     *  Condition 'test2!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test2!=NULL' is always true
     */
    printf("Test 2: %s -> %s\n", test2 != NULL ? test2 : "(null)", 
           is_binary_string(test2) ? "binary" : "not binary");
    /* Possible weaknesses found:
     *  Condition 'test3!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test3!=NULL' is always true
     */
    printf("Test 3: %s -> %s\n", test3 != NULL ? test3 : "(null)", 
           is_binary_string(test3) ? "binary" : "not binary");
    /* Possible weaknesses found:
     *  Condition 'test4!=NULL' is always true
     *  Condition 'test4!=NULL' is always true [knownConditionTrueFalse]
     */
    printf("Test 4: %s -> %s\n", test4 != NULL ? test4 : "(null)", 
           is_binary_string(test4) ? "binary" : "not binary");
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always false
     *  Condition 'test5!=NULL' is always false [knownConditionTrueFalse]
     */
    printf("Test 5: %s -> %s\n", test5 != NULL ? test5 : "(null)", 
           /* Possible weaknesses found:
            *  Condition 'is_binary_string(test5)' is always false [knownConditionTrueFalse]
            *  Calling function 'is_binary_string' returns 0
            *  Condition 'is_binary_string(test5)' is always false
            */
           is_binary_string(test5) ? "binary" : "not binary");
    
    return 0;
}