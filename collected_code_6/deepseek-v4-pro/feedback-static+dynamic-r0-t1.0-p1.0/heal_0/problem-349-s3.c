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
    const char *test1 = "101010";
    const char *test2 = "10201";
    const char *test3 = "";
    const char *test4 = "1";
    const char *test5 = NULL;
    
    printf("Test 1: %s -> %s\n", test1 != NULL ? test1 : "(null)", 
           is_binary_string(test1) ? "binary" : "not binary");
    printf("Test 2: %s -> %s\n", test2 != NULL ? test2 : "(null)", 
           is_binary_string(test2) ? "binary" : "not binary");
    printf("Test 3: %s -> %s\n", test3 != NULL ? test3 : "(null)", 
           is_binary_string(test3) ? "binary" : "not binary");
    printf("Test 4: %s -> %s\n", test4 != NULL ? test4 : "(null)", 
           is_binary_string(test4) ? "binary" : "not binary");
    printf("Test 5: %s -> %s\n", test5 != NULL ? test5 : "(null)", 
           is_binary_string(test5) ? "binary" : "not binary");
    
    return 0;
}