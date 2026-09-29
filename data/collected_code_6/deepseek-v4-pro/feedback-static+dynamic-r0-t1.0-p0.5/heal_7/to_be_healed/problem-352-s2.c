#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[256] = {0};
    size_t length = strnlen(str, 256);
    
    if (length >= 256) {
        return false;
    }
    
    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = 1;
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test1="abcdef"', assigned value is "abcdef"
     */
    const char *test1 = "abcdef";
    /* Possible weaknesses found:
     *  Assignment 'test2="hello"', assigned value is "hello"
     */
    const char *test2 = "hello";
    /* Possible weaknesses found:
     *  Assignment 'test3=""', assigned value is ""
     */
    const char *test3 = "";
    /* Possible weaknesses found:
     *  Assignment 'test4="aA"', assigned value is "aA"
     */
    const char *test4 = "aA";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    /* Possible weaknesses found:
     *  Condition 'test1!=NULL' is always true
     *  Condition 'test1!=NULL' is always true [knownConditionTrueFalse]
     */
    if (test1 != NULL) {
        printf("%s: %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    } else {
        /* Possible weaknesses found:
         *  Condition 'all_unique_chars(test1)' is always true
         *  Condition 'all_unique_chars(test1)' is always true [knownConditionTrueFalse]
         *  Calling function 'all_unique_chars' returns 1
         */
        printf("NULL: %s\n", all_unique_chars(test1) ? "unique" : "not unique");
    }
    
    /* Possible weaknesses found:
     *  Condition 'test2!=NULL' is always true
     *  Condition 'test2!=NULL' is always true [knownConditionTrueFalse]
     */
    if (test2 != NULL) {
        printf("%s: %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    } else {
        /* Possible weaknesses found:
         *  Condition 'all_unique_chars(test2)' is always true [knownConditionTrueFalse]
         *  Condition 'all_unique_chars(test2)' is always true
         *  Calling function 'all_unique_chars' returns 1
         */
        printf("NULL: %s\n", all_unique_chars(test2) ? "unique" : "not unique");
    }
    
    /* Possible weaknesses found:
     *  Condition 'test3!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test3!=NULL' is always true
     */
    if (test3 != NULL) {
        printf("%s: %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    } else {
        /* Possible weaknesses found:
         *  Condition 'all_unique_chars(test3)' is always true [knownConditionTrueFalse]
         *  Condition 'all_unique_chars(test3)' is always true
         *  Calling function 'all_unique_chars' returns 1
         */
        printf("NULL: %s\n", all_unique_chars(test3) ? "unique" : "not unique");
    }
    
    /* Possible weaknesses found:
     *  Condition 'test4!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test4!=NULL' is always true
     */
    if (test4 != NULL) {
        printf("%s: %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    } else {
        /* Possible weaknesses found:
         *  Condition 'all_unique_chars(test4)' is always true [knownConditionTrueFalse]
         *  Condition 'all_unique_chars(test4)' is always true
         *  Calling function 'all_unique_chars' returns 1
         */
        printf("NULL: %s\n", all_unique_chars(test4) ? "unique" : "not unique");
    }
    
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'test5!=NULL' is always false
     */
    if (test5 != NULL) {
        printf("%s: %s\n", test5, all_unique_chars(test5) ? "unique" : "not unique");
    } else {
        /* Possible weaknesses found:
         *  Condition 'all_unique_chars(test5)' is always true
         *  Calling function 'all_unique_chars' returns 1
         *  Condition 'all_unique_chars(test5)' is always true [knownConditionTrueFalse]
         */
        printf("NULL: %s\n", all_unique_chars(test5) ? "unique" : "not unique");
    }
    
    return 0;
}