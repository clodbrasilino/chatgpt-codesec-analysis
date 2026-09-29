#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    const char *test5 = NULL;
    
    printf("Test 1 (abcdefg): %s\n", all_unique_chars(test1) ? "unique" : "not unique");
    printf("Test 2 (hello): %s\n", all_unique_chars(test2) ? "unique" : "not unique");
    printf("Test 3 (empty): %s\n", all_unique_chars(test3) ? "unique" : "not unique");
    printf("Test 4 (aA): %s\n", all_unique_chars(test4) ? "unique" : "not unique");
    /* Possible weaknesses found:
     *  Condition 'all_unique_chars(test5)' is always true [knownConditionTrueFalse]
     *  Calling function 'all_unique_chars' returns 1
     *  Condition 'all_unique_chars(test5)' is always true
     */
    printf("Test 5 (NULL): %s\n", all_unique_chars(test5) ? "unique" : "not unique");
    
    return 0;
}