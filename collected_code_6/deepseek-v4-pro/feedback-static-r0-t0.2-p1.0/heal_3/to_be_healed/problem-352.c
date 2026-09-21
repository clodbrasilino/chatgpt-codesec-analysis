#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    unsigned char *seen = (unsigned char *)calloc(UCHAR_MAX + 1, sizeof(unsigned char));
    if (seen == NULL) {
        return true;
    }
    
    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            free(seen);
            return false;
        }
        seen[c] = 1;
    }
    
    free(seen);
    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    /* Possible weaknesses found:
     *  Variable 'test5' is assigned a value that is never used. [unreadVariable]
     */
    const char *test5 = NULL;
    
    printf("Test 1 (%s): %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    printf("Test 2 (%s): %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    printf("Test 3 (%s): %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    printf("Test 4 (%s): %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    
    printf("Test 5 (NULL): unique\n");
    
    return 0;
}