#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

bool is_concatenation(const char *str, const char *base) {
    if (str == NULL || base == NULL) {
        return false;
    }
    
    size_t str_len = strnlen(str, SIZE_MAX / 2);
    size_t base_len = strnlen(base, SIZE_MAX / 2);
    
    if (base_len == 0) {
        return str_len == 0;
    }
    
    if (str_len % base_len != 0) {
        return false;
    }
    
    size_t repetitions = str_len / base_len;
    
    for (size_t i = 0; i < repetitions; i++) {
        if (strncmp(str + (i * base_len), base, base_len) != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test_str1 = "abcabcabc";
    const char *test_base1 = "abc";
    printf("%s is concatenation of %s: %s\n", 
           test_str1, test_base1, 
           is_concatenation(test_str1, test_base1) ? "true" : "false");
    
    const char *test_str2 = "hello world";
    const char *test_base2 = "hello";
    printf("%s is concatenation of %s: %s\n", 
           test_str2, test_base2, 
           is_concatenation(test_str2, test_base2) ? "true" : "false");
    
    const char *test_str3 = "aaaaaa";
    const char *test_base3 = "aa";
    printf("%s is concatenation of %s: %s\n", 
           test_str3, test_base3, 
           is_concatenation(test_str3, test_base3) ? "true" : "false");
    
    const char *test_str4 = "";
    const char *test_base4 = "abc";
    printf("\"%s\" is concatenation of %s: %s\n", 
           test_str4, test_base4, 
           is_concatenation(test_str4, test_base4) ? "true" : "false");
    
    const char *test_str5 = "abcabcab";
    const char *test_base5 = "abc";
    printf("%s is concatenation of %s: %s\n", 
           test_str5, test_base5, 
           is_concatenation(test_str5, test_base5) ? "true" : "false");
    
    const char *test_str6 = NULL;
    const char *test_base6 = "abc";
    /* Possible weaknesses found:
     *  Assignment 'result=is_concatenation(test_str6,test_base6)', assigned value is 0
     *  Calling function 'is_concatenation' returns 0
     */
    bool result = is_concatenation(test_str6, test_base6);
    printf("NULL is concatenation of %s: %s\n", 
           test_base6, 
           /* Possible weaknesses found:
            *  Condition 'result' is always false
            *  Condition 'result' is always false [knownConditionTrueFalse]
            */
           result ? "true" : "false");
    
    return 0;
}