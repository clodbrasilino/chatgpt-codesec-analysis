#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    unsigned char seen[UCHAR_MAX + 1] = {0};
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = 1;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("Test 1 (abcdefg): %s\n", all_unique_chars(test1) ? "unique" : "not unique");
    printf("Test 2 (hello): %s\n", all_unique_chars(test2) ? "unique" : "not unique");
    printf("Test 3 (empty): %s\n", all_unique_chars(test3) ? "unique" : "not unique");
    printf("Test 4 (aA): %s\n", all_unique_chars(test4) ? "unique" : "not unique");
    
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'test5!=NULL' is always false
     */
    if (test5 != NULL) {
        printf("Test 5 (NULL): %s\n", all_unique_chars(test5) ? "unique" : "not unique");
    } else {
        printf("Test 5 (NULL): not unique\n");
    }
    
    return 0;
}