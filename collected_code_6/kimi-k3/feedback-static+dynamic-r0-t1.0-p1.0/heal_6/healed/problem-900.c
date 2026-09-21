#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }
    
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    char num_str[32];
    int ret = snprintf(num_str, sizeof(num_str), "%d", num);
    if (ret < 0 || (size_t)ret >= sizeof(num_str)) {
        return 0;
    }
    
    size_t num_len = (size_t)ret;
    
    if (strncmp(str, num_str, num_len) == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    const char *test1 = "123hello";
    const char *test2 = "456world";
    const char *test3 = "  789test";
    const char *test4 = "no_number";
    
    printf("Test 1: %s\n", starts_with_number(test1, 123) ? "true" : "false");
    printf("Test 2: %s\n", starts_with_number(test2, 123) ? "true" : "false");
    printf("Test 3: %s\n", starts_with_number(test3, 789) ? "true" : "false");
    printf("Test 4: %s\n", starts_with_number(test4, 999) ? "true" : "false");
    
    return 0;
}