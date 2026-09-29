#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    unsigned char seen[UCHAR_MAX + 1] = {0};
    
    for (size_t i = 0; str[i] != '\0'; i++) {
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
    const char *test5 = NULL;
    
    printf("Test 1 (%s): %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    printf("Test 2 (%s): %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    printf("Test 3 (%s): %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    printf("Test 4 (%s): %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    
    if (test5 != NULL) {
        printf("Test 5 (%s): %s\n", test5, all_unique_chars(test5) ? "unique" : "not unique");
    } else {
        printf("Test 5 (NULL): null input\n");
    }
    
    return 0;
}