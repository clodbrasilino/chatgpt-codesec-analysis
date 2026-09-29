#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isAlternating(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    if (len < 2) {
        return false;
    }
    
    char first = str[0];
    char second = str[1];
    
    if (first == second) {
        return false;
    }
    
    for (size_t i = 2; i < len; i++) {
        char expected = (i % 2 == 0) ? first : second;
        if (str[i] != expected) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test1 = "ababab";
    const char *test2 = "xyxy";
    const char *test3 = "aaaa";
    const char *test4 = "abc";
    const char *test5 = "ab";
    const char *test6 = "";
    const char *test7 = NULL;
    
    printf("Test 1 \"%s\": %s\n", test1, isAlternating(test1) ? "true" : "false");
    printf("Test 2 \"%s\": %s\n", test2, isAlternating(test2) ? "true" : "false");
    printf("Test 3 \"%s\": %s\n", test3, isAlternating(test3) ? "true" : "false");
    printf("Test 4 \"%s\": %s\n", test4, isAlternating(test4) ? "true" : "false");
    printf("Test 5 \"%s\": %s\n", test5, isAlternating(test5) ? "true" : "false");
    printf("Test 6 \"%s\": %s\n", test6, isAlternating(test6) ? "true" : "false");
    
    if (test7 != NULL) {
        printf("Test 7 \"%s\": %s\n", test7, isAlternating(test7) ? "true" : "false");
    } else {
        printf("Test 7 NULL: false\n");
    }
    
    return 0;
}