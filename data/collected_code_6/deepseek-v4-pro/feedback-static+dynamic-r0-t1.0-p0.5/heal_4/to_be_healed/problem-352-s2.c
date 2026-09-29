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
    
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'i>=256' is redundant or the array 'str[1]' is accessed at index 256, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    for (size_t i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Array index out of bounds
         *  Either the condition 'i>=256' is redundant or the array 'str[3]' is accessed at index 256, which is out of bounds. [arrayIndexOutOfBoundsCond]
         */
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'i>=256' is not redundant
         */
        if (i >= 256) {
            return false;
        }
        seen[c] = 1;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1 ? test1 : "NULL", all_unique_chars(test1) ? "unique" : "not unique");
    printf("%s: %s\n", test2 ? test2 : "NULL", all_unique_chars(test2) ? "unique" : "not unique");
    printf("%s: %s\n", test3 ? test3 : "NULL", all_unique_chars(test3) ? "unique" : "not unique");
    printf("%s: %s\n", test4 ? test4 : "NULL", all_unique_chars(test4) ? "unique" : "not unique");
    /* Possible weaknesses found:
     *  Condition 'test5' is always false
     *  Condition 'all_unique_chars(test5)' is always true [knownConditionTrueFalse]
     *  Condition 'test5' is always false [knownConditionTrueFalse]
     *  Condition 'all_unique_chars(test5)' is always true
     *  Calling function 'all_unique_chars' returns 1
     */
    printf("%s: %s\n", test5 ? test5 : "NULL", all_unique_chars(test5) ? "unique" : "not unique");
    
    return 0;
}