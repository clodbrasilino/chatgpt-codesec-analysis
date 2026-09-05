#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_number_at_end(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    
    if (len == 0) {
        return false;
    }
    
    size_t pos = len - 1;
    
    while (pos > 0 && isdigit((unsigned char)str[pos])) {
        pos--;
    }
    
    if (isdigit((unsigned char)str[pos])) {
        return true;
    }
    
    if (pos < len - 1 && (str[pos] == '+' || str[pos] == '-')) {
        return true;
    }
    
    return false;
}

int main(void) {
    const char *test1 = "Hello123";
    const char *test2 = "Hello";
    const char *test3 = "Number-456";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("Test 1: %s -> %s\n", test1, has_number_at_end(test1) ? "true" : "false");
    printf("Test 2: %s -> %s\n", test2, has_number_at_end(test2) ? "true" : "false");
    printf("Test 3: %s -> %s\n", test3, has_number_at_end(test3) ? "true" : "false");
    printf("Test 4: (empty) -> %s\n", has_number_at_end(test4) ? "true" : "false");
    printf("Test 5: NULL -> %s\n", has_number_at_end(test5) ? "true" : "false");
    
    return 0;
}