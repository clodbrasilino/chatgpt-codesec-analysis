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
    size_t length = 0;
    
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'length>=256' is redundant or the array 'str[1]' is accessed at index 255, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (length < 256 && str[length] != '\0') {
        length++;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'length>=256' is not redundant
     */
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
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    printf("%s: %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    printf("%s: %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    printf("%s: %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    
    /* Possible weaknesses found:
     *  Condition 'test5==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test5==NULL' is always true
     */
    if (test5 == NULL) {
        /* Possible weaknesses found:
         *  Calling function 'all_unique_chars' returns 1
         *  Condition 'all_unique_chars(test5)' is always true [knownConditionTrueFalse]
         *  Condition 'all_unique_chars(test5)' is always true
         */
        printf("NULL: %s\n", all_unique_chars(test5) ? "unique" : "not unique");
    } else {
        printf("%s: %s\n", test5, all_unique_chars(test5) ? "unique" : "not unique");
    }
    
    return 0;
}